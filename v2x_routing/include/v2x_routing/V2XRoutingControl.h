//
// Created by Christoph Pilz on 07.09.2021.
//
// Description:
// TBA
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

#ifndef V2X_ROUTING_PLATFORM_V2XROUTINGCONTROL_H
#define V2X_ROUTING_PLATFORM_V2XROUTINGCONTROL_H

#include <map>
#include <string>

#include "util/interfaces/NonAssignable.h"
#include "util/interfaces/Stoppable.h"
#include "util/logger/LoggingFacility.h"

class V2XRoutingControl : public Stoppable, public NonAssignable {
public:
    V2XRoutingControl(int cycle_time_ms = 1000,
                         std::string v2x_routing_control_type = "V2XRoutingControl",
                         Logger::LogLevel log_level = Logger::LogLevel::WARN);

    virtual ~V2XRoutingControl();

    virtual uint32_t Configure();

    virtual uint32_t StartUp();

    virtual uint32_t ShutDown();

    virtual uint32_t Cleanup();

    /// Default core thread method that handles routing
    virtual void run() override;

    // getter/setter

    /// Returns the type of the v2x routing control
    /// \return v2x_routing_control_type_ ... std::string, N/D ... if not defined
    std::string V2XRoutingControlType();

protected:
    Logger *logger_;

    bool is_configured_;
    bool is_up_;

    int cycle_time_ms_;

private:
    std::string v2x_routing_control_type_;

};

#endif //V2X_ROUTING_PLATFORM_V2XROUTINGCONTROL_H
