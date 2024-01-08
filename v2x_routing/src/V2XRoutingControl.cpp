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

#include "V2XRoutingControl.h"

#include <sstream>

#include "util/logger/ClassStandardOutputLogger.h"

// --- --- Public --- ---
V2XRoutingControl::V2XRoutingControl(int cycle_time_ms, std::string v2x_routing_control_type, Logger::LogLevel log_level) {
    cycle_time_ms_ = cycle_time_ms;
    v2x_routing_control_type_ = v2x_routing_control_type;
    logger_ = new ClassStandardOutputLogger(log_level, v2x_routing_control_type_);

    is_configured_ = false;
    is_up_ = false;
}

V2XRoutingControl::~V2XRoutingControl() {
    delete logger_;
}

uint32_t V2XRoutingControl::Configure() {
    logger_->WriteErrorEntry("Configure(): not implemented");
    return -1;
}

uint32_t V2XRoutingControl::StartUp() {
    logger_->WriteErrorEntry("StartUp(): not implemented");
    return -1;
}

uint32_t V2XRoutingControl::ShutDown() {
    logger_->WriteErrorEntry("ShutDown(): not implemented");
    return -1;
}

uint32_t V2XRoutingControl::Cleanup() {
    logger_->WriteErrorEntry("Cleanup(): not implemented");
    return -1;
}

void V2XRoutingControl::run() {
    logger_->WriteInfoEntry("run()");

    // control loop
    while (stopRequested() == false) {
        logger_->WriteErrorEntry("run(): not implemented");

        // yield each cycle
        if(cycle_time_ms_ == 0)
            std::this_thread::yield();
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(cycle_time_ms_));
    }

    logger_->WriteInfoEntry("run(): end");
}

// --- --- Getter/Setter --- ---

std::string V2XRoutingControl::V2XRoutingControlType() {
    return v2x_routing_control_type_;
}

// --- --- Protected --- ---


// --- --- Private --- ---
