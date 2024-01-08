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

#include "CommunicationControl.h"

#include <sstream>

#include <limits.h>
#include <unistd.h>

#include "util/logger/ClassStandardOutputLogger.h"
#include "util/v2x_backend/V2XDefines.h"

#include "v2x_interface_control/MQTTInterfaceConnection.h"
#include "v2x_interface_control/UnexITSG5InterfaceConnection.h"

#include "input_handling_strategies/ZmqSimpleInputHandlingStrategy.h"
#include "output_handling_strategies/ZmqSimpleOutputHandlingStrategy.h"

// --- --- Public --- ---
std::string CommunicationControl::ADDRESS_MQTT = "127.0.0.1";
std::string CommunicationControl::ADDRESS_UNEX = "192.168.23.3";

std::string CommunicationControl::CERT_KEY_STORE = "/tmp/certs/client.pem";
std::string CommunicationControl::CERT_TRUST_STORE = "/tmp/certs/ca.crt";

CommunicationControl::CommunicationControl(int cycle_time_ms, std::string communication_control_type,
                                           Logger::LogLevel log_level) {
    cycle_time_ms_ = cycle_time_ms;
    communication_control_type_ = communication_control_type;
    logger_ = new ClassStandardOutputLogger(log_level, communication_control_type_);

    input_handling_strategy_ = new ZmqSimpleInputHandlingStrategy("ZMQ-SIHS", logger_->GetLogLevel());
    output_handling_strategy_ = new ZmqSimpleOutputHandlingStrategy("ZMQ-SOHS", logger_->GetLogLevel());

    is_configured_ = false;
    is_up_ = false;

    input_thread_ = nullptr;
    output_thread_ = nullptr;
}

CommunicationControl::~CommunicationControl() {
    delete output_thread_;
    delete input_thread_;

    delete output_handling_strategy_;
    delete input_handling_strategy_;

    delete logger_;
}

uint32_t CommunicationControl::Configure() {
    logger_->WriteInfoEntry("Configure()");

    if (is_configured_) {
        logger_->WriteInfoEntry("Configure(): already configured -> done");
        return 0;
    }

    /* variables */
    std::ostringstream oss;

    /* get system stuff */
    gethostname(hostname_, HOST_NAME_MAX);

    /* create V2X interfaces */
    // Unex SOM301-E (v1.7 only allows 4 casters and 8 caster configs
    logger_->WriteDebugEntry("Configure(): V2X interfaces - Unex");
    std::vector<unsigned int> btp_ports_unex;
    btp_ports_unex.push_back(V2XDefines::BTP_PORT_CA);
    btp_ports_unex.push_back(V2XDefines::BTP_PORT_DEN);
    btp_ports_unex.push_back(V2XDefines::BTP_PORT_IVI);
    btp_ports_unex.push_back(V2XDefines::BTP_PORT_GPC);
    connections_.push_back(new UnexITSG5InterfaceConnection(ADDRESS_UNEX, btp_ports_unex, logger_->GetLogLevel()));

    // MQTT
    logger_->WriteDebugEntry("Configure(): V2X interfaces - MQTT");
    connections_.push_back(new MQTTInterfaceConnection(
            ADDRESS_MQTT,
            CERT_KEY_STORE, CERT_TRUST_STORE,
            hostname_,
            logger_->GetLogLevel()
            ));

    /* V2X interface configuration */
    // print configuration
    oss.str("");
    oss.clear();
    oss << "Configure(): Interface Configuration" << std::endl;
    for (V2XInterfaceConnection *v2x_ic: connections_) {
        oss << "- " << v2x_ic->ConnectionType() << std::endl;
    }
    logger_->WriteInfoEntry(oss.str());

    /* Configure Strategies */
    // InputHandlingStrategy
    logger_->WriteDebugEntry("Configure(): input handling strategy");
    input_handling_strategy_->SetConnectionsReference(connections_);
    input_handling_strategy_->Configure();

    // OutputHandlingStrategy
    logger_->WriteDebugEntry("Configure(): output handling strategy");
    output_handling_strategy_->SetConnectionsReference(connections_);
    output_handling_strategy_->Configure();

    is_configured_ = true;
    logger_->WriteInfoEntry("Configure(): done");
    return 0;
}

uint32_t CommunicationControl::StartUp() {
    logger_->WriteInfoEntry("StartUp()");

    if (!is_configured_) {
        logger_->WriteErrorEntry("StartUp(): not yet configured -> Configure() first!");
        return -1;
    }

    if (is_up_) {
        logger_->WriteInfoEntry("StartUp(): already UP -> done");
        return 0;
    }

    // variables
    int ret;
    std::ostringstream oss;

    // connect V2X interfaces
    logger_->WriteDebugEntry("StartUp(): V2X interfaces");
    for (V2XInterfaceConnection *ic: connections_) {
        ret = ic->Connect();
        if (ret != 0) {
            oss.str("");
            oss.clear();
            oss << "StartUp(): could not connect " << ic->ConnectionType();
            logger_->WriteErrorEntry(oss.str());
            ic->stop();
        }
    }

    // startup InputHandlingStrategy
    logger_->WriteDebugEntry("StartUp(): input handling strategy");
    input_handling_strategy_->StartUp();

    // startup OutputHandlingStrategy
    logger_->WriteDebugEntry("StartUp(): output handling strategy");
    output_handling_strategy_->StartUp();

    is_up_ = true;
    logger_->WriteInfoEntry("StartUp(): done");
    return 0;
}

uint32_t CommunicationControl::ShutDown() {
    logger_->WriteInfoEntry("ShutDown()");

    if (!is_up_) {
        logger_->WriteInfoEntry("ShutDown(): already DOWN -> done");
        return 0;
    }

    // variables
    int ret;
    int ret_shutdown = 0;
    std::ostringstream oss;

    // ShutDown OutputHandlingStrategy
    logger_->WriteDebugEntry("ShutDown(): output handling strategy");
    output_handling_strategy_->ShutDown();

    // ShutDown InputHandlingStrategy
    logger_->WriteDebugEntry("ShutDown(): input handling strategy");
    input_handling_strategy_->ShutDown();

    // close V2X interfaces
    logger_->WriteDebugEntry("ShutDown(): V2X interfaces");
    for (V2XInterfaceConnection *ic : connections_) {
        ret = ic->Close();
        if (ret != 0) {
            oss.str("");
            oss.clear();
            oss << "ShutDown(): could not close " << ic->ConnectionType();
            logger_->WriteErrorEntry(oss.str());
            ret_shutdown = -1;
            logger_->WriteInfoEntry("ShutDown(): trying to close other connections");
        }
    }

    is_up_ = false;
    logger_->WriteInfoEntry("StartUp(): done");
    return ret_shutdown;
}

uint32_t CommunicationControl::Cleanup() {
    logger_->WriteInfoEntry("Cleanup()");

    if (is_up_) {
        logger_->WriteInfoEntry("Cleanup(): still up -> ShutDown() first!");
        return -1;
    }

    // Cleanup OutputHandlingStrategy
    logger_->WriteDebugEntry("Cleanup(): output handling strategy");
    output_handling_strategy_->Cleanup();

    // Cleanup InputHandlingStrategy
    logger_->WriteDebugEntry("Cleanup(): input handling strategy");
    input_handling_strategy_->Cleanup();

    // delete V2X interfaces
    logger_->WriteDebugEntry("Cleanup(): V2X interfaces");
    for (V2XInterfaceConnection *ic : connections_) {
        delete ic;
        ic = nullptr;
    }

    logger_->WriteInfoEntry("Cleanup(): done");
    return 0;
}

void CommunicationControl::run() {
    logger_->WriteInfoEntry("run()");

    // run V2X interfaces
    logger_->WriteDebugEntry("run(): V2X interfaces");
    for (V2XInterfaceConnection *ic : connections_) {
        ic->run();
    }

    // run InputHandlingStrategy
    logger_->WriteInfoEntry("run(): start input thread ...");
    if (input_thread_ == nullptr) {
        input_thread_ = new std::thread([&]() {
            input_handling_strategy_->run();
        });
    } else
        logger_->WriteWarnEntry("run(): input_thread_ might be already running");

    // run OutputHandlingStrategy
    logger_->WriteInfoEntry("run(): start output thread ...");
    if (output_thread_ == nullptr) {
        output_thread_ = new std::thread([&]() {
            output_handling_strategy_->run();
        });
    } else
        logger_->WriteWarnEntry("run(): input_thread_ might be already running");

    // control loop
    while (stopRequested() == false) {
        logger_->WriteTraceEntry("run(): loop start");

        // monitor threads
        if (input_handling_strategy_->stopRequested()) {
            logger_->WriteWarnEntry("run(): input_handling_strategy_->stopRequested() ... going to stop");
            stop();
        }
        if (output_handling_strategy_->stopRequested()) {
            logger_->WriteWarnEntry("run(): output_handling_strategy_->stopRequested() ... going to stop");
            stop();
        }

        // yield each cycle
        std::this_thread::sleep_for(std::chrono::milliseconds(cycle_time_ms_));
    }

    // stopping threads
    logger_->WriteInfoEntry("run(): stopping threads ...");
    output_handling_strategy_->stop();
    input_handling_strategy_->stop();

    // run V2X interfaces
    logger_->WriteDebugEntry("run(): stopping V2X interfaces");
    for (V2XInterfaceConnection *ic : connections_) {
        ic->stop();
    }

    // waiting for threads to stop
    logger_->WriteInfoEntry("run(): waiting for stopped threads ...");
    if (output_thread_ != nullptr) {
        output_thread_->join();
        delete output_thread_;
        output_thread_ = nullptr;
    }
    if (input_thread_ != nullptr) {
        input_thread_->join();
        delete input_thread_;
        input_thread_ = nullptr;
    }

    logger_->WriteInfoEntry("run(): end");
}

// --- --- Getter/Setter --- ---

std::string CommunicationControl::CommunicationControlType() {
    return communication_control_type_;
}

// --- --- Protected --- ---


// --- --- Private --- ---
