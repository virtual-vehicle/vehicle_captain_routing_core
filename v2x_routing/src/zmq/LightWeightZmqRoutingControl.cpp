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


#include "zmq/LightWeightZmqRoutingControl.h"

#include <sstream>
#include <sys/stat.h>
#include <langinfo.h>

#include "util/v2x_backend/V2XDefines.h"

extern "C" {
#include "vcits/parser/Decoder.h"
#include "vcits/cam/ItsPduHeader.h"
#include "vcits/vccontainer/RawRxMessage.h"
#include "vcits/vccontainer/RawTxMessage.h"
}

// --- --- Public --- ---

LightWeightZmqRoutingControl::LightWeightZmqRoutingControl(
        std::string envelope_raw_prefix, std::string envelope_v2x_prefix,
        int cycle_time_ms, std::string v2x_routing_control_type, Logger::LogLevel log_level)
        : BaseZmqRoutingControl(cycle_time_ms, v2x_routing_control_type, log_level) {
    envelope_raw_prefix_ = envelope_raw_prefix;
    envelope_v2x_prefix_ = envelope_v2x_prefix;
}

LightWeightZmqRoutingControl::~LightWeightZmqRoutingControl() {
}

// --- --- Getter/Setter --- ---


// --- --- Protected --- ---

//void BaseZmqRoutingControl::RunRemoteLocal(){
//    logger_->WriteInfoEntry("RunRemoteLocal()");
//
//    // variables
//    zmq::message_t msg;
//
//    // control loop
//    while (stopRequested() == false) {
//        logger_->WriteTraceEntry("RunRemoteLocal(): loop cycle");
//        if(zmq_socket_remote_in_->recv(msg, zmq::recv_flags::dontwait))
//            zmq_socket_local_out_->send(msg, zmq::send_flags::none);
//
//        // yield each cycle
//        if(cycle_time_ms_ == 0)
//            std::this_thread::yield();
//        else
//            std::this_thread::sleep_for(std::chrono::milliseconds(cycle_time_ms_));
//    }
//
//    logger_->WriteInfoEntry("RunRemoteLocal(): end");
//}

void LightWeightZmqRoutingControl::RunLocalRemote(){
    logger_->WriteInfoEntry("RunLocalRemote()");

    // variables
    zmq::message_t msg;
    zmq::message_t extracted_msg;
    unsigned int msg_id;

    // control loop
    while (stopRequested() == false) {
//        logger_->WriteTraceEntry("RunLocalRemote(): loop cycle");
        // raw messages - from local interfaces
        if(zmq_socket_local_in_->recv(msg, zmq::recv_flags::dontwait)){
            // extract msg and ID before sending
            ExtractV2XMessage(extracted_msg, msg);
            msg_id = GetV2XMessageID(extracted_msg);

            // TODO: GN management goes here
            // - e.g. check remain hop limit

            // create envelopes
            zmq::message_t msg_envelope_raw (envelope_raw_prefix_);
            zmq::message_t msg_envelope_v2x (envelope_v2x_prefix_ + V2XDefines::V2X_MSG_FROM_ID[msg_id] + zmq_separator_);

            // send raw data
            zmq_socket_remote_out_->send(msg_envelope_raw, zmq::send_flags::sndmore);
            zmq_socket_remote_out_->send(msg, zmq::send_flags::none);

            // send v2x message only
            zmq_socket_remote_out_->send(msg_envelope_v2x, zmq::send_flags::sndmore);
            zmq_socket_remote_out_->send(extracted_msg, zmq::send_flags::none);
        }

        // yield each cycle
        std::this_thread::sleep_for(std::chrono::microseconds(100));  // 0.1ms = 10000Hz
    }

    logger_->WriteInfoEntry("RunLocalRemote(): end");
}

void LightWeightZmqRoutingControl::RunRemoteLocal() {
    logger_->WriteInfoEntry("RunRemoteLocal()");

    // variables
    zmq::message_t envelope;
    zmq::message_t msg;
    unsigned int msg_id;

    // control loop
    while (stopRequested() == false) {
//        logger_->WriteTraceEntry("RunRemoteLocal(): loop cycle");

        // receive envelope
        if (zmq_socket_remote_in_->recv(envelope, zmq::recv_flags::dontwait)) {
            // receive message
            if (zmq_socket_remote_in_->recv(msg, zmq::recv_flags::dontwait)) {
                std::string envelope_string = std::string(static_cast<char *>(envelope.data()), envelope.size());

                if (envelope_string.compare(envelope_v2x_prefix_) == 0) {
                    // we got a non-classified v2x message
                    logger_->WriteTraceEntry("RunRemoteLocal(): non-classified v2x message found");

                    // get message ID
                    msg_id = GetV2XMessageID(msg);

                    // create envelope
                    zmq::message_t msg_envelope_v2x (envelope_v2x_prefix_ + V2XDefines::V2X_MSG_FROM_ID[msg_id] + zmq_separator_);
                    logger_->WriteTraceEntry("RunRemoteLocal(): created new envelope: \""
                                + envelope_v2x_prefix_ + V2XDefines::V2X_MSG_FROM_ID[msg_id] + zmq_separator_
                                + "\" for msg_id: " + std::to_string(msg_id));

                    // send message to local
                    zmq_socket_local_out_->send(msg_envelope_v2x, zmq::send_flags::sndmore);
                    zmq_socket_local_out_->send(msg, zmq::send_flags::none);
                } else if(envelope_string.rfind(envelope_v2x_prefix_.c_str(), 0) == 0) {
                    // we got an already classified v2x message
                    logger_->WriteTraceEntry("RunRemoteLocal(): already classified v2x message found -> relaying to local");

                    // send message to local
                    zmq_socket_local_out_->send(envelope, zmq::send_flags::sndmore);
                    zmq_socket_local_out_->send(msg, zmq::send_flags::none);
                } else {
                    // something is wrong?
                    logger_->WriteInfoEntry("RunRemoteLocal(): non v2x message found (\"" + envelope_string + "\") ... not implemented");
                }
            }
            else {
                //something is wrong?
                logger_->WriteWarnEntry("RunRemoteLocal(): missing payload for envelope");
            }
        }

        // yield each cycle
        std::this_thread::sleep_for(std::chrono::microseconds(100));  // 0.1ms = 10000Hz
    }

    logger_->WriteInfoEntry("RunRemoteLocal(): end");
}

// --- --- Private --- ---
void LightWeightZmqRoutingControl::ExtractV2XMessage(zmq::message_t &extracted_message, zmq::message_t &msg){
    logger_->WriteTraceEntry("ExtractV2XMessage()");

    //variables
    RawRxMessage *raw_rx_message = nullptr;

    // decode message
    raw_rx_message = (RawRxMessage *) Decoder::decode(&asn_DEF_RawRxMessage, msg.data(), msg.size());

    if (raw_rx_message != nullptr) {
        logger_->WriteTraceEntry("ExtractV2XMessage(): got a valid RawRxMessage");
        if(raw_rx_message->payloadString != nullptr){
            logger_->WriteTraceEntry("ExtractV2XMessage(): got a v2x payload");
            extracted_message = zmq::message_t(raw_rx_message->payloadString->buf, raw_rx_message->payloadString->size);
        } else {
            logger_->WriteWarnEntry("ExtractV2XMessage(): no v2x payload in RawRxMessage");
        }
    } else {
        logger_->WriteWarnEntry("ExtractV2XMessage(): failed to decode RawRxMessage");
    }

    ASN_STRUCT_FREE(asn_DEF_RawRxMessage, raw_rx_message);
    raw_rx_message = nullptr;

    logger_->WriteTraceEntry("ExtractV2XMessage(): end");
}

unsigned int LightWeightZmqRoutingControl::GetV2XMessageID(zmq::message_t &msg) {
    logger_->WriteTraceEntry("GetV2XMessageID()");

    // variables
    unsigned int msg_id = 0;
    ItsPduHeader_t *its_pdu_header = nullptr;

    // decode
    its_pdu_header = (ItsPduHeader_t *) Decoder::decode(&asn_DEF_ItsPduHeader, msg.data(), msg.size());
    if (its_pdu_header != nullptr) {
        msg_id = its_pdu_header->messageID;
    } else {
        msg_id = V2XDefines::MSG_ID_UNKNOWN;
    }

    ASN_STRUCT_FREE(asn_DEF_ItsPduHeader, its_pdu_header);
    its_pdu_header = nullptr;
    return msg_id;

    logger_->WriteTraceEntry("GetV2XMessageID(): end");
}
