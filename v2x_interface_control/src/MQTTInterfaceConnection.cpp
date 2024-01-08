// -*- lsst-c++ -*-

/*
* VIF V2X Platform
* See COPYRIGHT file at the top of the source tree.
*
* This product includes software developed by the
* InSecTT Project (https://www.insectt.eu/).
*
* (Licensing)
* TBD
*/

#include "MQTTInterfaceConnection.h"
#include "../include/v2x_interface_control/MQTTInterfaceConnection.h"

#include <csignal>
#include <fstream>
#include <sstream>

#include <math.h>
#include <memory.h>
#include <time.h>

#include "util/encoder/base64.h"
#include "util/v2x_backend/V2XDefines.h"

extern "C" {
#include "vcits/parser/Encoder.h"
#include "vcits/vccontainer/LocalInfo.h"
#include "vcits/vccontainer/RawRxMessage.h"
#include "vcits/vccontainer/RawTxMessage.h"
}

// --- --- Public --- ---
const unsigned int MQTTInterfaceConnection::MQTT_MSG_EXPIRY_INTERVALL = 10;         // intervall in seconds
const bool MQTTInterfaceConnection::MQTT_NO_LOCAL = true;                           // Tell the broker we don't want our own messages sent back to us.
const int MQTTInterfaceConnection::MQTT_QOS = 1;                                    // The QoS to use for publishing and subscribing
const std::chrono::seconds MQTTInterfaceConnection::MQTT_TIMEOUT = std::chrono::seconds(10);    // intervall in seconds

std::string MQTTInterfaceConnection::CHANNEL_V2X_PREFIX = "v2x";
std::string MQTTInterfaceConnection::CHANNEL_BTP_PORT_PREFIX = "btp";
std::string MQTTInterfaceConnection::CHANNEL_STATUS_PREFIX = "status";

std::string MQTTInterfaceConnection::MSG_CONNECTION_CLOSING = "connection closing - good bye";
std::string MQTTInterfaceConnection::MSG_CONNECTION_ESTABLISHED = "connection established";
std::string MQTTInterfaceConnection::MSG_CONNECTION_LOST = "lost connection";

MQTTInterfaceConnection::MQTTInterfaceConnection(std::string server_address,
                                                 std::string cert_key_store,
                                                 std::string cert_trust_store,
                                                 std::string client_id,
                                                 Logger::LogLevel log_level)
        : V2XInterfaceConnection(std::string("MQTTInterfaceConnection-").append(server_address), log_level) {
    server_address_ = server_address;
    client_id_ = client_id;

    cert_key_store_ = cert_key_store;
    cert_trust_store_ = cert_trust_store;
}

MQTTInterfaceConnection::~MQTTInterfaceConnection() {
}

int32_t MQTTInterfaceConnection::Connect() {
    logger_->WriteInfoEntry("Connect()");

    /* local variables */
    std::ostringstream oss;

    /* some sanity checks */
    {
        ifstream trust_store(cert_trust_store_);
        if (!trust_store) {
            logger_->WriteErrorEntry("Connect(): the trust store file does not exist: <" + cert_trust_store_ + ">");
            return -1;
        }

        ifstream key_store(cert_key_store_);
        if (!key_store) {
            logger_->WriteErrorEntry("Connect(): the key store file does not exist: <" + cert_key_store_ + ">");
            return -1;
        }
    }

    /* prepare environment */
    // SSL options: https://github.com/eclipse/paho.mqtt.cpp/blob/master/src/samples/ssl_publish.cpp
    auto ssl_options = mqtt::ssl_options_builder()
            .trust_store(cert_trust_store_)
            .key_store(cert_key_store_)
            .enable_server_cert_auth(true)
            .error_handler([&](const std::string &msg) {
                logger_->WriteErrorEntry("Connect(): SSL Error: " + msg);
            })
            .finalize();

    // last will text (LWT) message is broadcast to other users if connection is lost
    auto last_will_text = mqtt::message(CHANNEL_V2X_PREFIX + CHANNEL_STATUS_PREFIX,
                                        client_id_ + ": " + MSG_CONNECTION_LOST,
                                        MQTT_QOS,
                                        false);

    /* communication config */
    // set properties
    mqtt::properties connection_properties{
            {mqtt::property::SESSION_EXPIRY_INTERVAL, MQTT_MSG_EXPIRY_INTERVALL}
    };

    // set options
    auto connection_options = mqtt::connect_options_builder()
            .mqtt_version(MQTTVERSION_5)
            .properties(connection_properties)
            .clean_start(true)
            .will(std::move(last_will_text))
            .ssl(std::move(ssl_options))
//            .keep_alive_interval(std::chrono::seconds(1))     // implement keep alive status at some point
            .finalize();

    // create client
    client_ = std::make_shared<mqtt::async_client>("ssl://" + server_address_ + ":8883",
                                                   client_id_,
                                                   mqtt::create_options(MQTTVERSION_5));

    // create callback for connection lost
    client_->set_connection_lost_handler([&](const std::string &) {
        logger_->WriteErrorEntry("Connect(): " + client_id_ + ": connection lost");
    });

    /* start connection */
    try {
        // Connect using SSL/TLS
        logger_->WriteDebugEntry("Connect(): connecting ssl://" + server_address_ + ":8883 ...");
        mqtt::token_ptr connect_token = client_->connect(connection_options);
        logger_->WriteDebugEntry("Connect(): waiting ...");
        connect_token->wait();
        logger_->WriteInfoEntry("Connect(): connected.");

        // Send init status message
        auto msg = mqtt::make_message(CHANNEL_V2X_PREFIX + "/" + CHANNEL_STATUS_PREFIX,
                                      client_id_ + ": " + MSG_CONNECTION_ESTABLISHED,
                                      MQTT_QOS,
                                      false);
        client_->publish(msg)->wait_for(MQTT_TIMEOUT);
        logger_->WriteDebugEntry(
                "Connect(): init message sent to: \"" + CHANNEL_V2X_PREFIX + "/" + CHANNEL_STATUS_PREFIX + "\"");

        // subscribe to topics
        client_->subscribe(CHANNEL_V2X_PREFIX + "/" + CHANNEL_BTP_PORT_PREFIX, MQTT_QOS)->wait();

        // start consuming
        client_->start_consuming();
    }
    catch (const mqtt::exception &exception) {
        logger_->WriteErrorEntry("Connect(): " + std::string(exception.what()));
        return -1;
    }

    return 0;
}

int32_t MQTTInterfaceConnection::Close() {
    logger_->WriteInfoEntry("Close()");

    /* local variables */
    std::ostringstream oss;

    /* release the connector */
    try {
        // Send close status message
        auto msg = mqtt::make_message(CHANNEL_V2X_PREFIX + "/" + CHANNEL_STATUS_PREFIX,
                                      client_id_ + ": " + MSG_CONNECTION_CLOSING,
                                      MQTT_QOS,
                                      false);
        client_->publish(msg)->wait_for(MQTT_TIMEOUT);
        logger_->WriteDebugEntry(
                "Close(): closing message sent to: \"" + CHANNEL_V2X_PREFIX + "/" + CHANNEL_STATUS_PREFIX + "\"");

        client_->disconnect()->wait();
        logger_->WriteInfoEntry("Close(): " + client_id_ + " - successful");
    }
    catch (const mqtt::exception &exception) {
        logger_->WriteErrorEntry("Close(): " + std::string(exception.what()));
        return -1;
    }

    /* destroy client_ */
    client_.reset();

    return 0;
}

// --- --- Protected --- ---
//    std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> UnexITSG5InterfaceConnection::DoReceive() override; //C++17
std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> MQTTInterfaceConnection::DoReceive() {
    logger_->WriteTraceEntry("DoReceive()");

    /* local variables */
    void *rawRxMessageStream = nullptr;
    ssize_t rawRxMessageStreamSize = 0;
    ostringstream oss;
//    std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> msg; //C++17
    std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> msg = std::experimental::nullopt;
    RawRxMessage rawRxMessage;

    // initialize message with 0
    memset((void *) &rawRxMessage, 0, sizeof(rawRxMessage));

    /* receive from connector */
    try {
        auto mqtt_msg = client_->consume_message();
        if (mqtt_msg) {
            // the V2X message is enclosed between "<" and ">"
            std::string mqtt_payload = mqtt_msg->to_string();
            auto pos_left = mqtt_payload.find("<");
            auto pos_right = mqtt_payload.find(">");

            // find base64 encoded v2x msg
            if ( (pos_left != std::string::npos) || (pos_right != std::string::npos)) {
                // continue parsing
                std::string encoded_msg = mqtt_payload.substr(pos_left+1, pos_right-pos_left-1);
                std::vector<BYTE> decoded_msg = base64_decode(encoded_msg);

                /* Pack Time and GeoData at time of reception */
                // PackLocalInfo(&rawRxMessage)

                /* Pack V2X RX information into raw message */
                // PackRxInfo(&rawRxMessage) would goes here

                /* Put received msg into payload */
                rawRxMessage.payloadSize = decoded_msg.size();
                rawRxMessage.payloadString = (OCTET_STRING_t *) malloc(sizeof(OCTET_STRING_t));
                memset((void *)(rawRxMessage.payloadString), 0, sizeof(OCTET_STRING_t));

                if(rawRxMessage.payloadString == nullptr) {
                    logger_->WriteFatalEntry("DoReceive(): malloc failed ... out of memory?");
                }

                OCTET_STRING_fromBuf(rawRxMessage.payloadString, (char *)(&decoded_msg[0]), decoded_msg.size());

                /* validate and convert RawRxMessage to asn1 stream and create tuple */
                Encoder::validate_constraints(&asn_DEF_RawRxMessage, &rawRxMessage);
                rawRxMessageStreamSize = Encoder::encode(&asn_DEF_RawRxMessage, nullptr, &rawRxMessage, &rawRxMessageStream);

        //        msg = std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> {std::make_tuple(v2x_asn1_stream, len)}; //C++17
        //TODO set BTP_PORT, where it came from!
                msg = std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> {
                    std::make_tuple(std::make_pair(rawRxMessageStream, rawRxMessageStreamSize), V2XDefines::BTP_PORT_NONE)};
            }
        }
    }
    catch (const mqtt::exception &exception) {
        logger_->WriteErrorEntry("DoReceive(): " + std::string(exception.what()));
    }

    return msg;
}

void MQTTInterfaceConnection::DoSend(std::tuple<std::pair<void *, size_t>, unsigned int> outgoing_msg) {
    logger_->WriteTraceEntry("DoSend()");

    /* variables */
    std::string asn_string = base64_encode((unsigned char*)std::get<0>(outgoing_msg).first, std::get<0>(outgoing_msg).second);

    /* source */
    // send to specific topic: https://github.com/eclipse/paho.mqtt.cpp/blob/master/src/samples/mqttpp_chat.cpp

    /* send */
    try {
        auto msg = mqtt::make_message(CHANNEL_V2X_PREFIX + "/" + CHANNEL_BTP_PORT_PREFIX + "/" + std::to_string(std::get<1>(outgoing_msg)),
                                      client_id_ + "(" + std::to_string(std::get<1>(outgoing_msg)) + "): <" + asn_string + ">",
                                      MQTT_QOS,
                                      false);
        client_->publish(msg)->wait_for(MQTT_TIMEOUT);
        logger_->WriteTraceEntry("DoSend(): " +
                                 client_id_ + "(" + std::to_string(std::get<1>(outgoing_msg)) + "): <" + asn_string + ">" + " sent to: \"" +
                                 CHANNEL_V2X_PREFIX + "/" + CHANNEL_BTP_PORT_PREFIX + "/" + std::to_string(std::get<1>(outgoing_msg)) + "\"");
    }
    catch (const mqtt::exception &exception) {
        logger_->WriteErrorEntry("DoSend(): " + std::string(exception.what()));
    }

    free(std::get<0>(outgoing_msg).first);
}

// --- --- Private --- ---

//void UnexITSG5InterfaceConnection::PackRxInfo(RawRxMessage *rawRxMessage, itsg5_rx_info_t *rx_info) {
//    /* just some packing to be done */
//    rawRxMessage->rxInfo.timestamp.sec = rx_info->timestamp.tv_sec;
//    rawRxMessage->rxInfo.timestamp.usec = rx_info->timestamp.tv_usec;
//    rawRxMessage->rxInfo.rssi = rx_info->rssi;
//    rawRxMessage->rxInfo.dataRate = rx_info->data_rate;
//    rawRxMessage->rxInfo.trafficClassID = rx_info->traffic_class_id;
//    rawRxMessage->rxInfo.remainHopLimit = rx_info->remain_hop_limit;
//    rawRxMessage->rxInfo.security.status = rx_info->security.status;
//    rawRxMessage->rxInfo.security.itsAID = rx_info->security.its_aid;
//    rawRxMessage->rxInfo.security.sspLen = rx_info->security.ssp_len;
//    OCTET_STRING_fromBuf(&rawRxMessage->rxInfo.security.ssp, (char *)rx_info->security.ssp, SSP_LENGTH);
//    rawRxMessage->rxInfo.positionInfo.latitude = rx_info->position_info.latitude;
//    rawRxMessage->rxInfo.positionInfo.longitude = rx_info->position_info.longitude;
//    rawRxMessage->rxInfo.areaTypeInfo.type = rx_info->area_type_info.type;
//    rawRxMessage->rxInfo.areaTypeInfo.distanceA = rx_info->area_type_info.distance_a;
//    rawRxMessage->rxInfo.areaTypeInfo.distanceB = rx_info->area_type_info.distance_b;
//    rawRxMessage->rxInfo.areaTypeInfo.angle = rx_info->area_type_info.angle;
//    OCTET_STRING_fromBuf(&rawRxMessage->rxInfo.sourceMacAddress, (char *)rx_info->source_mac_addr, MAC_ADDR_SIZE);
//}
