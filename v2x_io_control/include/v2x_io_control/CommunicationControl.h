//
// Created by Christoph Pilz on 01.09.2021.
//
// Description:
// CommunicationControl is the central routing control of the VIF V2X Platform Project
// - uses InputHandlerStrategies to collect V2X messages.
// - uses OutputHandlerStrategies to distribute V2X messages.
// - uses ZMQ to for routing of messages
// - uses ZMQ for local and external V2X manipulation
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
// [] add triple-/ comments for documentation of methods
// [] create v2x_interface_rating for ratinghandler, and have a InterfaceRatingHandler as protected member, for the communication control
// [] Configure() should set the In/Out Handlers via Configure(In=default, Out=default)
// [] should implement Configurable -> also for handling as exceptions
//

#ifndef V2X_ROUTING_PLATFORM_COMMUNICATIONCONTROL_H
#define V2X_ROUTING_PLATFORM_COMMUNICATIONCONTROL_H

#include <list>
#include <map>

#include <limits.h>

#include "util/interfaces/NonAssignable.h"
#include "util/interfaces/Stoppable.h"
#include "util/logger/LoggingFacility.h"

#include "InputHandlingStrategy.h"
#include "OutputHandlingStrategy.h"

#include "v2x_interface_control/V2XInterfaceConnection.h"

class CommunicationControl : public NonAssignable, public Stoppable {
public:
    // constants
    static std::string ADDRESS_MQTT;
    static std::string ADDRESS_UNEX;

    static std::string CERT_KEY_STORE;
    static std::string CERT_TRUST_STORE;

    CommunicationControl(int cycle_time_ms = 1000,
                         std::string communication_control_type = "CommunicationControl",
                         Logger::LogLevel log_level = Logger::LogLevel::WARN);

    virtual ~CommunicationControl();

    virtual uint32_t Configure();

    virtual uint32_t StartUp();

    virtual uint32_t ShutDown();

    virtual uint32_t Cleanup();

    /// Default core thread method that handles communication
    void run() override;

    // getter/setter

    /// Returns the type of the communication control
    /// \return communication_control_type_ ... std::string, N/D ... if not defined
    std::string CommunicationControlType();

protected:
    Logger *logger_;

    /// related to BTP port
    std::list<V2XInterfaceConnection *> connections_;

    InputHandlingStrategy *input_handling_strategy_;
    OutputHandlingStrategy *output_handling_strategy_;

    bool is_configured_;
    bool is_up_;

private:
    char hostname_[HOST_NAME_MAX];

    std::string communication_control_type_;

    int cycle_time_ms_;

    std::thread *input_thread_;
    std::thread *output_thread_;
};

#endif //V2X_ROUTING_PLATFORM_COMMUNICATIONCONTROL_H
