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


#include "ZmqSimpleOutputHandlingStrategy.h"

#include "util/exceptions/V2XPlatformExceptions.h"
#include "util/logger/ClassStandardOutputLogger.h"
#include "util/v2x_backend/V2XDefines.h"

// --- --- Public --- ---

ZmqSimpleOutputHandlingStrategy::ZmqSimpleOutputHandlingStrategy(std::string strategy_type, Logger::LogLevel log_level)
        : OutputHandlingStrategy(strategy_type, log_level) {
    envelope_v2x_prefix_ = "v2x.";
}

ZmqSimpleOutputHandlingStrategy::~ZmqSimpleOutputHandlingStrategy() {
}

void ZmqSimpleOutputHandlingStrategy::Configure(){
    logger_->WriteInfoEntry("Configure()");

    if(is_configured_) {
        logger_->WriteInfoEntry("Configure(): already configured -> done");
        return;
    }

    // create ZMQ context
    logger_->WriteDebugEntry("Configure(): ZMQ context");
    zmq_context_ = new zmq::context_t(1);

    // create ZMQ sockets
    logger_->WriteDebugEntry("Configure(): ZMQ sockets");
    zmq_socket_local_out_ = new zmq::socket_t(*zmq_context_, ZMQ_SUB);

    is_configured_ = true;
    logger_->WriteInfoEntry("Configure(): done");
}

void ZmqSimpleOutputHandlingStrategy::StartUp(){
    logger_->WriteInfoEntry("StartUp()");

    if(!is_configured_) {
        logger_->WriteErrorEntry("StartUp(): not yet configured -> Configure() first!");
        throw NotConfiguredException();
    }

    if(is_up_) {
        logger_->WriteInfoEntry("StartUp(): already UP -> done");
        return;
    }

    // connect ZMQ sockets
    logger_->WriteDebugEntry("StartUp(): connect ZMQ sockets");
    zmq_socket_local_out_->connect("ipc:///tmp/v2x/out/0");

    // set ZMQ socket options
    logger_->WriteDebugEntry("StartUp(): set ZMQ socket options");
    zmq_socket_local_out_->set(zmq::sockopt::subscribe, "");


    is_up_ = true;
    logger_->WriteInfoEntry("StartUp(): done");
}

void ZmqSimpleOutputHandlingStrategy::ShutDown(){
    logger_->WriteInfoEntry("ShutDown()");

    if(!is_up_) {
        logger_->WriteInfoEntry("ShutDown(): already DOWN -> done");
        return;
    }

    // nothing to do here
    logger_->WriteDebugEntry("ShutDown(): nothing to do here");

    is_up_ = false;
    logger_->WriteInfoEntry("ShutDown(): done");
}

void ZmqSimpleOutputHandlingStrategy::Cleanup(){
    logger_->WriteInfoEntry("Cleanup()");

    if(is_up_) {
        logger_->WriteInfoEntry("Cleanup(): still up -> ShutDown() first!");
        throw StillUpException();
    }

    // delete ZMQ sockets
    logger_->WriteDebugEntry("Cleanup(): ZMQ sockets");
    delete zmq_socket_local_out_;
    zmq_socket_local_out_ = nullptr;

    // delete ZMQ context
    logger_->WriteDebugEntry("Cleanup(): ZMQ context");
    delete zmq_context_;
    zmq_context_ = nullptr;

    logger_->WriteInfoEntry("Cleanup(): done");
}

// --- --- Protected --- ---

uint32_t ZmqSimpleOutputHandlingStrategy::HandleOutput() {
    logger_->WriteTraceEntry("HandleOutput()");

    zmq::message_t envelope;
    zmq::message_t msg;
    unsigned int msg_envelope_id;

    // receive envelope
    if (zmq_socket_local_out_->recv(envelope, zmq::recv_flags::dontwait)) {
        // receive message
        if (zmq_socket_local_out_->recv(msg, zmq::recv_flags::dontwait)) {
            std::string envelope_string = std::string(static_cast<char *>(envelope.data()), envelope.size());

            // v2x message ?
            if(envelope_string.rfind(envelope_v2x_prefix_.c_str(), 0) == 0) {
                logger_->WriteTraceEntry("HandleOutput(): got v2x message from " + envelope_string);

                // get the message id from envelope ("v2x.cam." -> "cam")
                msg_envelope_id = V2XDefines::V2X_ID_FROM_MSG[envelope_string.substr(envelope_v2x_prefix_.size(), envelope_string.size() - envelope_v2x_prefix_.size() - 1)];

                // message type to port mapping
                if (msg_envelope_id == V2XDefines::MSG_ID_NONE) {
                    // NONE type message - dropping
                    logger_->WriteDebugEntry("HandleOutput(): dropping v2x message from " + envelope_string + "(substring: \"" + envelope_string.substr(envelope_v2x_prefix_.size(), envelope_string.size() - envelope_v2x_prefix_.size() - 1) + "\")");
                } else if (msg_envelope_id == V2XDefines::MSG_ID_CAM) {
                    // CA
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_CA);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_DENM) {
                    // DEN
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_DEN);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_MAPEM) {
                    // RLT
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_RLT);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_SPATEM) {
                    // TLM
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_TLM);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_SAEM) {
                    // SA
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_SA);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_IVIM) {
                    // IVI
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_IVI);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_SREM) {
                    // TLC1
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_TLC1);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_SSEM) {
                    // TLC2
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_TLC2);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_CPM) {
                    // CP
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_CP);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_EVCSN
                        || msg_envelope_id == V2XDefines::MSG_ID_POI) {
                    // EVCSN POI
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_POI);
                } else if (false) {
                    // TPG
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_TPG);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_EV_RSR) {
                    // CHARGING
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_CHARGING);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_RTCMEM) {
                    // GPC
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_GPC);
                } else if (false) {
                    // CTL
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_CTL);
                } else if (false) {
                    // CRL
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_CRL);
                } else if (false) {
                    // CERT REQU
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_CERT_REQUEST);
                } else if (false) {
                    // MCD
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_MCD);
                } else if (msg_envelope_id == V2XDefines::MSG_ID_VAM) {
                    // VA
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_VA);
                } else if (false) {
                    // IMZ
                    SendV2XMessageToPort(msg, V2XDefines::BTP_PORT_IMZ);
                } else {
                    // unknown ... random message sending not implemented
                    logger_->WriteDebugEntry("HandleOutput(): sending of v2x message from " + envelope_string + "not yet implemented");
                }
            }
        }
    }

    return 0;
}

void ZmqSimpleOutputHandlingStrategy::SendV2XMessageToPort(zmq::message_t &msg, unsigned int btp_port) {
    logger_->WriteTraceEntry("SendV2XMessageToPort(): got message for port " + std::to_string(btp_port));

    // variables
    void *v2x_msg_buffer;
    size_t v2x_msg_size = msg.size();
    std::tuple<std::pair<void *, size_t>, unsigned int> v2x_msg;

    for (V2XInterfaceConnection *v2x_ic: connections_reference_) {
        // allocate memory for the v2x message
        v2x_msg_buffer = malloc(v2x_msg_size);
        if (v2x_msg_buffer == nullptr)
            throw std::runtime_error("HandleOutput(): malloc returned nullptr");

        // copy v2x_msg and create an optional
        memcpy(v2x_msg_buffer, msg.data(), v2x_msg_size);
        v2x_msg = std::make_tuple(std::make_pair(v2x_msg_buffer, v2x_msg_size), btp_port);

        // send with the interface
        v2x_ic->Send(v2x_msg);
    }

    // memory is freed by interface after sending

    logger_->WriteTraceEntry("SendV2XMessageToPort(): done");
}


// --- --- Private --- ---
