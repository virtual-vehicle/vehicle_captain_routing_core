//
// Created by <Christoph Pilz> on 15.07.2021.
//
// Description:
// Trying different things for Logging
// Not for production!!!
//
// Author(s): "Christoph Pilz"
// Copyright: "Copyright 2021, VIF V2X Platform Project"
// Credits: ["Christoph Pilz", "Werner Ziegelwanger "]
// License: "GPL"
// Version: "1.0.1"
// Maintainer: "Christoph Pilz"
// E-Mail: "christoph.pilz@v2c2.at"
// Status = "Production"
//
// Reference to used code:
// Full-Code (https://developer-blog.net/professionelles-loggen-unter-c/)
//
// Possible Improvements:
// [] (refactor) upgrade to C++17 (Full original Code), as soon as project is C++17
//

#ifndef V2X_ROUTING_PLATFORM_EXPERIMENTALOUTPUTLOGGER_H
#define V2X_ROUTING_PLATFORM_EXPERIMENTALOUTPUTLOGGER_H

#pragma once

#include "LoggingFacility.h"

#include <iostream>

class ExperimentalOutputLogger : public LoggingFacility {
public:
    ExperimentalOutputLogger(LogLevel log_level) : LoggingFacility(log_level) {};

protected:
    virtual void DoWriteTraceEntry(std::string entry) override {
        std::cout << "[TRACE] " << entry << std::endl;
    }

    virtual void DoWriteDebugEntry(std::string entry) override {
        std::cout << "[DEBUG] " << entry << std::endl;
    }

    virtual void DoWriteInfoEntry(std::string entry) override {
        std::cout << "[INFO] " << entry << std::endl;
    }

    virtual void DoWriteWarnEntry(std::string entry) override {
        std::cout << "[WARNING] " << entry << std::endl;
    }

    virtual void DoWriteErrorEntry(std::string entry) override {
        std::cout << "[ERROR] " << entry << std::endl;
    }

    virtual void DoWriteFatalEntry(std::string entry) override {
        std::cout << "[FATAL] " << entry << std::endl;
    }
};

#endif //V2X_ROUTING_PLATFORM_EXPERIMENTALOUTPUTLOGGER_H