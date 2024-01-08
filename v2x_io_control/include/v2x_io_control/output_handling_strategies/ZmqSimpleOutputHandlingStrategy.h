//
// Created by Christoph Pilz on 01.09.2021.
//
// Description:
// The ZmqSimpleOutputHandlingStrategy takes all messages from the local ZMQ socket and sends each message with every connected interface
//
// Author(s): "Christoph Pilz"
// Copyright: "Copyright 2021, VIF V2X Platform Project"
// Credits: [""]
// License: "TBD"
// Version: "TBD"
// Maintainer: "Christoph Pilz"
// E-Mail: "christoph.pilz@v2c2.at"
// Status = "Production"
//
// (Optional)Reference to used code:
// <Description1 what was used> (<Link>)
// <Description2 what was used> (<Link>)
//
// Possible Improvements:
// [] triple-/ for methods
// [] switch to C++17 ASAP (Unex dependencies)
//

#ifndef V2X_ROUTING_PLATFORM_ZMQSIMPLEOUTPUTHANDLINGSTRATEGY_H
#define V2X_ROUTING_PLATFORM_ZMQSIMPLEOUTPUTHANDLINGSTRATEGY_H

#include "OutputHandlingStrategy.h"

#include <string>

#include "zmq.hpp"

class ZmqSimpleOutputHandlingStrategy : public OutputHandlingStrategy {
public:
    /// Constructor, sets the strategy type and LogLevel
    ZmqSimpleOutputHandlingStrategy(std::string strategy_type = "ZmqSimpleOutputHandlingStrategy-DefaultName", Logger::LogLevel log_level = Logger::LogLevel::WARN);

    ///Destructor
    virtual ~ZmqSimpleOutputHandlingStrategy();

    virtual void Configure() override;

    virtual void StartUp() override;

    virtual void ShutDown() override;

    virtual void Cleanup() override;

protected:
    /// Takes V2X messages from ZMQ local out and distributes them to respective interface ports
    /// \return 0 on success
    virtual uint32_t HandleOutput() override;

    /// Takes a V2X message and sends them to all interfaces mapped to specified btp_port
    /// \param msg to send
    /// \param btp_port to send to
    virtual void SendV2XMessageToPort(zmq::message_t &msg, unsigned int btp_port);

    zmq::context_t *zmq_context_;
    zmq::socket_t *zmq_socket_local_out_;

    std::string envelope_v2x_prefix_;

private:

};

#endif //V2X_ROUTING_PLATFORM_ZMQSIMPLEOUTPUTHANDLINGSTRATEGY_H
