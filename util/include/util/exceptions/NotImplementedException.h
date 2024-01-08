//
// Created by Christoph Pilz on 13.09.2021.
//
// Description:
// Exception, if something is not yet implemented
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
//

#ifndef V2X_ROUTING_PLATFORM_NOTIMPLEMENTEDEXCEPTION_H
#define V2X_ROUTING_PLATFORM_NOTIMPLEMENTEDEXCEPTION_H

#pragma once

#include <exception>

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException() : std::logic_error("Function not yet implemented") { };
};

#endif //V2X_ROUTING_PLATFORM_NOTIMPLEMENTEDEXCEPTION_H
