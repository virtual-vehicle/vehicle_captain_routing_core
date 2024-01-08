//
// Created by Christoph Pilz on 23.08.2021.
//
// Description:
// makes a class non-assignable
//
// Author(s): "firegurafiku@stackoverflow.com, Christoph Pilz"
// Copyright: "Copyright 2021, VIF V2X Platform"
// Credits: ["firegurafiku@stackoverflow"]
// License: "TBD"
// Version: "TBD"
// Maintainer: "Christoph Pilz"
// E-Mail: "christoph.pilz@v2c2.at"
// Status = "Production"
//
// Reference to used code:
// Sample Code (https://stackoverflow.com/questions/6077143/disable-copy-constructor)
//
// Possible Improvements:
// [] License
//

#ifndef V2X_ROUTING_PLATFORM_NONASSIGNABLE_H
#define V2X_ROUTING_PLATFORM_NONASSIGNABLE_H

#pragma once

class NonAssignable {
public:
    NonAssignable(NonAssignable const&) = delete;
    NonAssignable& operator=(NonAssignable const&) = delete;
    NonAssignable() {}
};

#endif //V2X_ROUTING_PLATFORM_NONASSIGNABLE_H
