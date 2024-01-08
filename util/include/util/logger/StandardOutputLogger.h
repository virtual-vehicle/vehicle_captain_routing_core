//
// Created by <Christoph Pilz> on 15.07.2021.
//
// Description:
// Standard Output Logger that logs to the console
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

#ifndef V2X_ROUTING_PLATFORM_STANDARDOUTPUTLOGGER_H
#define V2X_ROUTING_PLATFORM_STANDARDOUTPUTLOGGER_H

#pragma once

#include "LoggingFacility.h"

#include <iostream>

class StandardOutputLogger : public LoggingFacility {
public:
    StandardOutputLogger(LogLevel log_level) : LoggingFacility(log_level) {};

protected:
    /// Prints the log entry to stdout with format "[TRACE] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteTraceEntry(std::string entry) override {
        std::cout << "[TRACE] " << entry << std::endl;
    }

    /// Prints the log entry to stdout with format "[DEBUG] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteDebugEntry(std::string entry) override {
        std::cout << "[DEBUG] " << entry << std::endl;
    }

    /// Prints the log entry to stdout with format "[INFO] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteInfoEntry(std::string entry) override {
        std::cout << "[INFO] " << entry << std::endl;
    }

    /// Prints the log entry to stdout with format "[WARNING] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteWarnEntry(std::string entry) override {
        std::cout << "[WARNING] " << entry << std::endl;
    }

    /// Prints the log entry to stdout with format "[ERROR] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteErrorEntry(std::string entry) override {
        std::cout << "[ERROR] " << entry << std::endl;
    }

    /// Prints the log entry to stdout with format "[FATAL] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteFatalEntry(std::string entry) override {
        std::cout << "[FATAL] " << entry << std::endl;
    }
};

#endif //V2X_ROUTING_PLATFORM_STANDARDOUTPUTLOGGER_H