//
// Created by <Christoph Pilz> on 16.08.2022.
//
// Description:
// Implementation of a Vehicle-to-Network (V2N) connection with MQTT
//
// Author(s): "Christoph Pilz"
// Copyright: "Copyright 2022, VIF V2X Platform Project"
// Credits: [""]
// License: "TBD"
// Version: "TBD"
// Maintainer: "Christoph Pilz"
// E-Mail: "christoph.pilz@v2c2.at"
// Status = "Production"
//
// Possible Improvements:
// [] switch to C++17 if possible and change experimental::optional
// [] implement the callback for a lost connection!
//      - reconnect
//      - print error
//      - sth else
// [] implement status message and interface timeout
// [] implement topics
//

#ifndef V2X_ROUTING_PLATFORM_MQTTINTERFACECONNECTION_H
#define V2X_ROUTING_PLATFORM_MQTTINTERFACECONNECTION_H

#pragma once

#include "V2XInterfaceConnection.h"

#include <chrono>

#include "mqtt/async_client.h"
#include "mqtt/topic.h"

#include "util/v2x_backend/V2XDefines.h"

extern "C" {
#include "vcits/vccontainer/RawRxMessage.h"
#include "vcits/vccontainer/RawTxMessage.h"
}

class MQTTInterfaceConnection : public V2XInterfaceConnection {
public:
    // constants
    static const unsigned int MQTT_MSG_EXPIRY_INTERVALL;
    static const bool MQTT_NO_LOCAL;
    static const int MQTT_QOS;
    static const std::chrono::seconds MQTT_TIMEOUT;

    static std::string CHANNEL_V2X_PREFIX;          // level 0
    static std::string CHANNEL_STATUS_PREFIX;       // level 1
    static std::string CHANNEL_BTP_PORT_PREFIX;     // level 1

    static std::string MSG_CONNECTION_CLOSING;
    static std::string MSG_CONNECTION_ESTABLISHED;
    static std::string MSG_CONNECTION_LOST;


    /// Constructor
    /// \param server_address ... server address for the MQTT server
    /// \param cert_key_store ... user key (from CA)
    /// \param cert_trust_store ... CA certificate
    /// \param client_id ... ID for messaging (i.e. vcaptainXXX)
    /// \param log_level ... Logger::LogLevel (Default = WARN)
    MQTTInterfaceConnection(std::string server_address,
                            std::string cert_key_store="client.pem",
                            std::string cert_trust_store="root-ca.crt",
                            std::string client_id="vcaptainXXX",
                            Logger::LogLevel log_level = Logger::LogLevel::WARN);

    /// Destructor warns on open connections
    virtual ~MQTTInterfaceConnection();

    /// Connect the interface
    /// \return 0 ... Success, -1 ... Error
    int32_t Connect() override;

    /// Close the interface
    /// \return 0 ... Success, -1 ... Error
    int32_t Close() override;

protected:

    /// receive V2X message
    /// \return V2X message and port, as optional tuple
    std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> DoReceive() override;
//    std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> DoReceive() override; //C++17

    /// send V2X messages
    /// \param outgoing_msg ... V2X message and port to send to
    void DoSend(std::tuple<std::pair<void *, size_t>, unsigned int> outgoing_msg) override;

private:
    std::string server_address_;
    std::string client_id_;

    std::string cert_key_store_;
    std::string cert_trust_store_;

    mqtt::async_client_ptr client_;


//    /// pack the rx info into the raw message
//    /// \param rawRxMessage [out] the rawRxMessage with filled rx info
//    /// \param rx_info [in] the received rx info
//    void PackRxInfo(RawRxMessage *rawRxMessage, itsg5_rx_info_t *rx_info);
};

#endif //V2X_ROUTING_PLATFORM_MQTTINTERFACECONNECTION_H
