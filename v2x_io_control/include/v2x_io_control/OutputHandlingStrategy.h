//
// Created by Christoph Pilz on 01.09.2021.
//
// Description:
// Parent <interface> for an Output Handling Strategy
// Specific *OutputHandlingStrategy has to provide means of handling the output to multiple V2X interfaces
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
// [] configure, startup, shutdown and cleanup should be a class
// [] configure, startup, shutdown and cleanup default implementation should throw exceptions.
//

#ifndef V2X_ROUTING_PLATFORM_OUTPUTHANDLINGSTRATEGY_H
#define V2X_ROUTING_PLATFORM_OUTPUTHANDLINGSTRATEGY_H

#include <list>
#include <map>

#include "util/interfaces/Configurable.h"
#include "util/interfaces/NonAssignable.h"
#include "util/interfaces/Stoppable.h"
#include "util/logger/LoggingFacility.h"

#include <v2x_interface_control/V2XInterfaceConnection.h>

class OutputHandlingStrategy : public Configurable, public NonAssignable, public Stoppable {
public:
    /// Constructor, sets the strategy type and LogLevel
    OutputHandlingStrategy(std::string strategy_type = "N/D", Logger::LogLevel log_level = Logger::LogLevel::WARN);

    ///Destructor
    virtual ~OutputHandlingStrategy();

    /// Returns the strategy type
    /// \return strategy_type_ ... std::string, N/D ... if not defined
    std::string StrategyType();

    virtual void Configure() override;

    virtual void StartUp() override;

    virtual void ShutDown() override;

    virtual void Cleanup() override;

    /// Default core thread method that handles the output strategy
    void run() override;

    // Getter & Setter

    void SetConnectionsReference(std::list<V2XInterfaceConnection *> &connections_reference);

protected:
    Logger *logger_;

    /// Abstract method that should handle the output
    /// \return 0 ... Success, -1 on Error
    virtual uint32_t HandleOutput() = 0;

    std::list<V2XInterfaceConnection *> connections_reference_;

private:
    std::string strategy_type_;

};

#endif //V2X_ROUTING_PLATFORM_OUTPUTHANDLINGSTRATEGY_H
