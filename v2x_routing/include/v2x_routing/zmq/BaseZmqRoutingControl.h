//
// Created by Christoph Pilz on 07.09.2021.
//
// Description:
// This Class is a Basic Implementation on ZMQ routing.
// It gets the messages from the local ZMQ socket and puts them on the remote ZMQ socket and vice versa.
// No additional magic involved
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
// [] add description in boilerplate
// [] add triple-/ comments for documentation of methods
// []
//

#ifndef V2X_ROUTING_PLATFORM_BASEZMQROUTINGCONTROL_H
#define V2X_ROUTING_PLATFORM_BASEZMQROUTINGCONTROL_H

#include "V2XRoutingControl.h"

#include "zmq.hpp"

class BaseZmqRoutingControl : public V2XRoutingControl {
public:
    BaseZmqRoutingControl(int cycle_time_ms = 0,
                          std::string v2x_routing_control_type = "BaseZmqRoutingControl",
                          Logger::LogLevel log_level = Logger::LogLevel::WARN);

    virtual ~BaseZmqRoutingControl();

    virtual uint32_t Configure() override;

    virtual uint32_t StartUp() override;

    virtual uint32_t ShutDown() override;

    virtual uint32_t Cleanup() override;

    /// Default core thread method that handles routing
    virtual void run() override;

protected:
    zmq::context_t *zmq_context_;
    zmq::socket_t *zmq_socket_local_in_;
    zmq::socket_t *zmq_socket_local_out_;
    zmq::socket_t *zmq_socket_remote_in_;
    zmq::socket_t *zmq_socket_remote_out_;

    std::string zmq_separator_;

    /// simply sends some heartbeat
    virtual void RunDiagnostic();

    /// simply takes the messages from the local socket and sends it to remote
    virtual void RunLocalRemote();

    /// simply takes the messages from the remote socket and sends it to local
    virtual void RunRemoteLocal();

private:
    std::thread *thread_diagnostic_;
    std::thread *thread_remote_local_;
    std::thread *thread_local_remote_;
};

#endif //V2X_ROUTING_PLATFORM_BASEZMQROUTINGCONTROL_H
