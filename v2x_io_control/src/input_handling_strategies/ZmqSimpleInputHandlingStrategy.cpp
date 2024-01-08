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


#include "ZmqSimpleInputHandlingStrategy.h"

//#include <optional> //C++17
#include <experimental/optional>

#include "util/exceptions/V2XPlatformExceptions.h"
#include "util/logger/ClassStandardOutputLogger.h"

// --- --- Public --- ---

ZmqSimpleInputHandlingStrategy::ZmqSimpleInputHandlingStrategy(std::string strategy_type, Logger::LogLevel log_level)
        : InputHandlingStrategy(strategy_type, log_level) {
}

ZmqSimpleInputHandlingStrategy::~ZmqSimpleInputHandlingStrategy() {
}

void ZmqSimpleInputHandlingStrategy::Configure(){
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
    zmq_socket_local_in_ = new zmq::socket_t(*zmq_context_, ZMQ_PUB);

    is_configured_ = true;
    logger_->WriteInfoEntry("Configure(): done");
}

void ZmqSimpleInputHandlingStrategy::StartUp(){
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
    zmq_socket_local_in_->connect("ipc:///tmp/v2x/in/0");

    // set ZMQ socket options
    logger_->WriteDebugEntry("StartUp(): set ZMQ socket options");


    is_up_ = true;
    logger_->WriteInfoEntry("StartUp(): done");
}

void ZmqSimpleInputHandlingStrategy::ShutDown(){
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

void ZmqSimpleInputHandlingStrategy::Cleanup(){
    logger_->WriteInfoEntry("Cleanup()");

    if(is_up_) {
        logger_->WriteInfoEntry("Cleanup(): still up -> ShutDown() first!");
        throw StillUpException();
    }

    // delete ZMQ sockets
    logger_->WriteDebugEntry("Cleanup(): ZMQ sockets");
    delete zmq_socket_local_in_;
    zmq_socket_local_in_ = nullptr;

    // delete ZMQ context
    logger_->WriteDebugEntry("Cleanup(): ZMQ context");
    delete zmq_context_;
    zmq_context_ = nullptr;

    logger_->WriteInfoEntry("Cleanup(): done");
}

// --- --- Protected --- ---

uint32_t ZmqSimpleInputHandlingStrategy::HandleInput() {
    logger_->WriteTraceEntry("HandleInput()");

    // variables
    std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> v2x_msg;

    // checks once for a new message on every interface and sends it to ZMQ
    for (V2XInterfaceConnection *v2x_ic : connections_reference_) {
        v2x_msg = v2x_ic->Receive();
        if (v2x_msg) {
            logger_->WriteDebugEntry("HandleInput(): got message - relay to ZMQ");
            // one might prioritise on port
            // std::get<0>(v2x_msg.value());

            // get raw v2x message
            void *v2x_msg_buffer = std::get<0>(v2x_msg.value()).first;
            size_t v2x_msg_size = std::get<0>(v2x_msg.value()).second;

            // create ZMQ message
            zmq::message_t zmq_msg(v2x_msg_size);
            memcpy(zmq_msg.data(), v2x_msg_buffer, v2x_msg_size);

            // send raw ZMQ message
            zmq_socket_local_in_->send(zmq_msg, zmq::send_flags::none);

            // free pointer of v2x message
            free(v2x_msg_buffer);
            v2x_msg_buffer = nullptr;
        }
    }
    return 0;
}


// --- --- Private --- ---
