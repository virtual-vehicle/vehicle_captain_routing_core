//
// Created by <Christoph Pilz> on 15.07.2021.
//
// Description:
// Logger that logs to the standard output and knows which class it's from.
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

#ifndef V2X_ROUTING_PLATFORM_CLASSSTANDARDOUTPUTLOGGER_H
#define V2X_ROUTING_PLATFORM_CLASSSTANDARDOUTPUTLOGGER_H

#pragma once

#include "LoggingFacility.h"

#include <iostream>

class ClassStandardOutputLogger : public LoggingFacility {
public:
    ClassStandardOutputLogger(LogLevel log_level, std::string class_name) : LoggingFacility(log_level) {
        class_name_ = class_name;
    }

protected:
    /// Prints the log entry to stdout with format "[TRACE][classname_] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteTraceEntry(std::string entry) override {
        std::cout << "[TRACE][" << class_name_ << "] " << entry << std::endl;
    }

    /// Prints the log entry to stdout with format "[DEBUG][classname_] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteDebugEntry(std::string entry) override {
        std::cout << "[DEBUG][" << class_name_ << "] " << entry << std::endl;
    }

    /// Prints the log entry to stdout with format "[INFO][classname_] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteInfoEntry(std::string entry) override {
        std::cout << "[INFO][" << class_name_ << "] " << entry << std::endl;
    }

    /// Prints the log entry to stdout with format "[WARNING][classname_] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteWarnEntry(std::string entry) override {
        std::cout << "[WARNING][" << class_name_ << "] " << entry << std::endl;
    }

    /// Prints the log entry to stdout with format "[ERROR][classname_] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteErrorEntry(std::string entry) override {
        std::cout << "[ERROR][" << class_name_ << "] " << entry << std::endl;
    }

    /// Prints the log entry to stdout with format "[FATAL][classname_] <entry>"
    /// \param entry ... logging entry
    virtual void DoWriteFatalEntry(std::string entry) override {
        std::cout << "[FATAL][" << class_name_ << "] " << entry << std::endl;
    }

private:
    std::string class_name_;
};

#endif //V2X_ROUTING_PLATFORM_CLASSSTANDARDOUTPUTLOGGER_H