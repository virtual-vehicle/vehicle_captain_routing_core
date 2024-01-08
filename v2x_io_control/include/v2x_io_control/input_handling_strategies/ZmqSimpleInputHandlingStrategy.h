//
// Created by Christoph Pilz on 01.09.2021.
//
// Description:
// The ZmqSimpleInputHandlingStrategy will collect all V2X messages straight from the input and put all messages into a local ZMQ input socket.
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

#ifndef V2X_ROUTING_PLATFORM_ZMQSIMPLEINPUTHANDLINGSTRATEGY_H
#define V2X_ROUTING_PLATFORM_ZMQSIMPLEINPUTHANDLINGSTRATEGY_H

#include "InputHandlingStrategy.h"

#include "zmq.hpp"

class ZmqSimpleInputHandlingStrategy : public InputHandlingStrategy {
public:
    /// Constructor, sets the strategy type and LogLevel
    ZmqSimpleInputHandlingStrategy(std::string strategy_type = "ZmqSimpleInputHandlingStrategy-DefaultName", Logger::LogLevel log_level = Logger::LogLevel::WARN);

    ///Destructor
    virtual ~ZmqSimpleInputHandlingStrategy();

    virtual void Configure() override;

    virtual void StartUp() override;

    virtual void ShutDown() override;

    virtual void Cleanup() override;

protected:
    virtual uint32_t HandleInput() override;

    zmq::context_t *zmq_context_;
    zmq::socket_t *zmq_socket_local_in_;
};

#endif //V2X_ROUTING_PLATFORM_ZMQSIMPLEINPUTHANDLINGSTRATEGY_H
