//
// Created by Christoph Pilz on 13.09.2021.
//
// Description:
// Adds Configure, StartUp, ShutDown and Cleanup methods
//
// Author(s): "Christoph Pilz"
// Copyright: "Copyright 2021, VIF V2X Platform"
// Credits: ["Thispointer.com"]
// License: "TBD"
// Version: "TBD"
// Maintainer: "Christoph Pilz"
// E-Mail: "christoph.pilz@v2c2.at"
// Status = "Production"
//
// Possible Improvements:
// [] License
// [] add integrity checks with exceptions (i.e., if Configure is not yet done, but StartUp called)
//

#ifndef V2X_ROUTING_PLATFORM_CONFIGURABLE_H
#define V2X_ROUTING_PLATFORM_CONFIGURABLE_H

#pragma once

class Configurable {
public:
    Configurable() : is_configured_(false), is_up_(false) {};

    virtual void Configure() = 0;

    virtual void StartUp() = 0;

    virtual void ShutDown() = 0;

    virtual void Cleanup() = 0;

protected:
    bool is_configured_;
    bool is_up_;
};

#endif //V2X_ROUTING_PLATFORM_CONFIGURABLE_H
