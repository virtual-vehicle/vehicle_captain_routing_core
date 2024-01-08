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


#include "zmq/BaseZmqRoutingControl.h"

#include <sstream>
#include <sys/stat.h>
#include <langinfo.h>

#include "util/logger/ClassStandardOutputLogger.h"

// --- --- Public --- ---

BaseZmqRoutingControl::BaseZmqRoutingControl(int cycle_time_ms, std::string v2x_routing_control_type,
                                             Logger::LogLevel log_level)
        : V2XRoutingControl(cycle_time_ms, v2x_routing_control_type, log_level) {
    thread_diagnostic_ = nullptr;
    thread_remote_local_ = nullptr;
    thread_local_remote_ = nullptr;

    zmq_separator_ = ".";
}

BaseZmqRoutingControl::~BaseZmqRoutingControl() {
    delete thread_diagnostic_;
    delete thread_local_remote_;
    delete thread_remote_local_;
}

uint32_t BaseZmqRoutingControl::Configure() {
    logger_->WriteInfoEntry("Configure()");

    if (is_configured_) {
        logger_->WriteInfoEntry("Configure(): already configured -> done");
        return 0;
    }

    // create ZMQ context
    logger_->WriteDebugEntry("Configure(): ZMQ context");
    zmq_context_ = new zmq::context_t(1);

    // create ZMQ sockets
    logger_->WriteDebugEntry("Configure(): ZMQ sockets");
    zmq_socket_local_in_ = new zmq::socket_t(*zmq_context_, ZMQ_SUB);
    zmq_socket_local_out_ = new zmq::socket_t(*zmq_context_, ZMQ_PUB);
    zmq_socket_remote_in_ = new zmq::socket_t(*zmq_context_, ZMQ_SUB);
    zmq_socket_remote_out_ = new zmq::socket_t(*zmq_context_, ZMQ_PUB);

    is_configured_ = true;
    logger_->WriteInfoEntry("Configure(): done");
    return 0;
}

uint32_t BaseZmqRoutingControl::StartUp() {
    logger_->WriteInfoEntry("StartUp()");

    if (!is_configured_) {
        logger_->WriteErrorEntry("StartUp(): not yet configured -> Configure() first!");
        return -1;
    }

    if (is_up_) {
        logger_->WriteInfoEntry("StartUp(): already UP -> done");
        return 0;
    }

    // bind ZMQ sockets
    logger_->WriteDebugEntry("StartUp(): bind ZMQ sockets");
    zmq_socket_local_in_->bind("ipc:///tmp/v2x/in/0");
    zmq_socket_local_out_->bind("ipc:///tmp/v2x/out/0");
    zmq_socket_remote_in_->bind("tcp://*:5555");
    zmq_socket_remote_out_->bind("tcp://*:5556");

    // set ZMQ socket options
    logger_->WriteDebugEntry("StartUp(): set ZMQ socket options");
    zmq_socket_local_in_->set(zmq::sockopt::subscribe, "");
    zmq_socket_remote_in_->set(zmq::sockopt::subscribe, "");


    is_up_ = true;
    logger_->WriteInfoEntry("StartUp(): done");
    return 0;
}

uint32_t BaseZmqRoutingControl::ShutDown() {
    logger_->WriteInfoEntry("ShutDown()");

    if (!is_up_) {
        logger_->WriteInfoEntry("ShutDown(): already DOWN -> done");
        return 0;
    }

    // nothing to do here
    logger_->WriteDebugEntry("ShutDown(): nothing to do here");

    is_up_ = false;
    logger_->WriteInfoEntry("ShutDown(): done");
    return 0;
}

uint32_t BaseZmqRoutingControl::Cleanup() {
    logger_->WriteInfoEntry("Cleanup()");

    if (is_up_) {
        logger_->WriteInfoEntry("Cleanup(): still up -> ShutDown() first!");
        return -1;
    }

    // delete ZMQ sockets
    logger_->WriteDebugEntry("Cleanup(): ZMQ sockets");
    delete zmq_socket_remote_out_;
    zmq_context_ = nullptr;
    delete zmq_socket_remote_in_;
    zmq_socket_remote_in_ = nullptr;
    delete zmq_socket_local_out_;
    zmq_socket_local_out_ = nullptr;
    delete zmq_socket_local_in_;
    zmq_socket_local_in_ = nullptr;

    // delete ZMQ context
    logger_->WriteDebugEntry("Cleanup(): ZMQ context");
    delete zmq_context_;
    zmq_context_ = nullptr;

    logger_->WriteInfoEntry("Cleanup(): done");
    return 0;
}

void BaseZmqRoutingControl::run() {
    logger_->WriteInfoEntry("run()");

    // diagnostic thread
    logger_->WriteInfoEntry("run(): start diagnostic thread ...");
    if (thread_diagnostic_ == nullptr) {
        thread_diagnostic_ = new std::thread([&]() {
            RunDiagnostic();
        });
    } else
        logger_->WriteInfoEntry("run(): thread_diagnostic_ might be already running");

    // remote-local thread
    logger_->WriteInfoEntry("run(): start remote-local thread ...");
    if (thread_remote_local_ == nullptr) {
        thread_remote_local_ = new std::thread([&]() {
            RunRemoteLocal();
        });
    } else
        logger_->WriteInfoEntry("run(): thread_remote_local_ might be already running");

    // local-remote thread
    logger_->WriteInfoEntry("run(): start local-remote thread ...");
    if (thread_local_remote_ == nullptr) {
        thread_local_remote_ = new std::thread([&]() {
            RunLocalRemote();
        });
    } else
        logger_->WriteWarnEntry("run(): thread_local_remote_ might be already running");

    // control loop
    while (stopRequested() == false) {

        // yield each cycle
        if (cycle_time_ms_ == 0)
            std::this_thread::yield();
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(cycle_time_ms_));
    }

    // waiting for threads to stop
    logger_->WriteInfoEntry("run(): waiting for stopped threads ...");
    if (thread_local_remote_ != nullptr) {
        thread_local_remote_->join();
        delete thread_local_remote_;
        thread_local_remote_ = nullptr;
    }
    if (thread_remote_local_ != nullptr) {
        thread_remote_local_->join();
        delete thread_remote_local_;
        thread_remote_local_ = nullptr;
    }
    if (thread_diagnostic_ != nullptr) {
        thread_diagnostic_->join();
        delete thread_diagnostic_;
        thread_diagnostic_ = nullptr;
    }

    logger_->WriteInfoEntry("run(): end");
}

// --- --- Getter/Setter --- ---


// --- --- Protected --- ---

void BaseZmqRoutingControl::RunDiagnostic() {
    logger_->WriteInfoEntry("RunDiagnostic()");

    // variables
    int diagnostic_cycle_time_ms = 1000;
    uint16_t heartbeat_counter = 0;

    // control loop
    while (stopRequested() == false) {
        logger_->WriteDebugEntry("RunDiagnostic(): heartbeat");

        // assemble heartbeat string
        std::string heartbeat_string = std::string("{\"heartbeat_counter\": ");
        heartbeat_string.append(std::to_string(heartbeat_counter));
        heartbeat_string.append("}");

        // send heartbeat data
        zmq::message_t msg_envelope_diagnostic_counter_local (std::string("hb.counter"));
        zmq::message_t msg_diagnostic_counter_local (heartbeat_string);
        zmq_socket_remote_out_->send(msg_envelope_diagnostic_counter_local, zmq::send_flags::sndmore);
        zmq_socket_remote_out_->send(msg_diagnostic_counter_local, zmq::send_flags::none);

        heartbeat_counter++;

        // sleep each cycle
        std::this_thread::sleep_for(std::chrono::milliseconds(diagnostic_cycle_time_ms));
    }

    logger_->WriteInfoEntry("RunDiagnostic(): end");
}

void BaseZmqRoutingControl::RunLocalRemote() {
    logger_->WriteInfoEntry("RunLocalRemote()");

    // variables
    zmq::message_t msg;

    // control loop
    while (stopRequested() == false) {
        logger_->WriteTraceEntry("RunLocalRemote(): loop cycle");
        if (zmq_socket_local_in_->recv(msg, zmq::recv_flags::dontwait))
            zmq_socket_remote_out_->send(msg, zmq::send_flags::none);

        // yield each cycle
        std::this_thread::sleep_for(std::chrono::microseconds(100));  // 0.1ms = 10000Hz
    }

    logger_->WriteInfoEntry("RunLocalRemote(): end");
}

void BaseZmqRoutingControl::RunRemoteLocal() {
    logger_->WriteInfoEntry("RunRemoteLocal()");

    // variables
    zmq::message_t msg;

    // control loop
    while (stopRequested() == false) {
        logger_->WriteTraceEntry("RunRemoteLocal(): loop cycle");
        if (zmq_socket_remote_in_->recv(msg, zmq::recv_flags::dontwait))
            zmq_socket_local_out_->send(msg, zmq::send_flags::none);

        // yield each cycle
        std::this_thread::sleep_for(std::chrono::microseconds(100));  // 0.1ms = 10000Hz
    }

    logger_->WriteInfoEntry("RunRemoteLocal(): end");
}

// --- --- Private --- ---