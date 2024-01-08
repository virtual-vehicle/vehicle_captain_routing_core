//
// Created by <Christoph Pilz> on 15.07.2021.
//
// Description:
// Logging Facility for Professional log-levels and independent implementations
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
// [] Implement this kind of Formatter for logging: https://stackoverflow.com/questions/12261915/how-to-throw-stdexceptions-with-variable-messages
//

#ifndef V2X_ROUTING_PLATFORM_LOGGINGFACILITY_H
#define V2X_ROUTING_PLATFORM_LOGGINGFACILITY_H

#pragma once

#include <memory>
#include <string>

class LoggingFacility {
public:
    enum class LogLevel {
        ALL = 0,
        TRACE = 1,
        DEBUG = 2,
        INFO = 3,
        WARN = 4,
        ERROR = 5,
        FATAL = 6,
        NONE = 7
    };

    LoggingFacility(LogLevel log_level) : log_level_(log_level) {};

    virtual ~LoggingFacility() = default;

    /// Checks the LogLevel setting; if accepted, passes the string to the DoWriteTraceEntry
    /// \param entry TRACE logging string
    void WriteTraceEntry(std::string entry) { if (log_level_ <= LogLevel::TRACE) { DoWriteTraceEntry(entry); }};

    /// Checks the LogLevel setting; if accepted, passes the string to the DoWriteDebugEntry
    /// \param entry DEBUG logging string
    void WriteDebugEntry(std::string entry) { if (log_level_ <= LogLevel::DEBUG) { DoWriteDebugEntry(entry); }};

    /// Checks the LogLevel setting; if accepted, passes the string to the DoWriteInfoEntry
    /// \param entry INFO logging string
    void WriteInfoEntry(std::string entry) { if (log_level_ <= LogLevel::INFO) { DoWriteInfoEntry(entry); }};

    /// Checks the LogLevel setting; if accepted, passes the string to the DoWriteWarnEntry
    /// \param entry WARN logging string
    void WriteWarnEntry(std::string entry) { if (log_level_ <= LogLevel::WARN) { DoWriteWarnEntry(entry); }};

    /// Checks the LogLevel setting; if accepted, passes the string to the DoWriteErrorEntry
    /// \param entry ERROR logging string
    void WriteErrorEntry(std::string entry) { if (log_level_ <= LogLevel::ERROR) { DoWriteErrorEntry(entry); }};

    /// Checks the LogLevel setting; if accepted, passes the string to the DoWriteFatalEntry
    /// \param entry FATAL logging string
    void WriteFatalEntry(std::string entry) { if (log_level_ <= LogLevel::FATAL) { DoWriteFatalEntry(entry); }};

    LogLevel GetLogLevel() { return log_level_; };

protected:
    virtual void DoWriteTraceEntry(std::string entry) = 0;

    virtual void DoWriteDebugEntry(std::string entry) = 0;

    virtual void DoWriteInfoEntry(std::string entry) = 0;

    virtual void DoWriteWarnEntry(std::string entry) = 0;

    virtual void DoWriteErrorEntry(std::string entry) = 0;

    virtual void DoWriteFatalEntry(std::string entry) = 0;

private:
    LogLevel log_level_ = LogLevel::NONE;
};

using Logger = LoggingFacility;


#endif //V2X_ROUTING_PLATFORM_LOGGINGFACILITY_H
