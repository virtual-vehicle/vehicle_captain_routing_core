//
// Created by Christoph Pilz on 23.08.2021.
//
// Description:
// Adds start and stop functionality to a class.
// A core thread can be run via class.run() and requested to stop via class.stop()
//
// Author(s): "Thispointer.com, Christoph Pilz"
// Copyright: "Copyright 2021, VIF V2X Platform"
// Credits: ["Thispointer.com"]
// License: "TBD"
// Version: "TBD"
// Maintainer: "Christoph Pilz"
// E-Mail: "christoph.pilz@v2c2.at"
// Status = "Production"
//
// Reference to used code:
// Sample Code (https://thispointer.com/c11-how-to-stop-or-terminate-a-thread/)
//
// Possible Improvements:
// [] License
//

#ifndef V2X_ROUTING_PLATFORM_STOPPABLE_H
#define V2X_ROUTING_PLATFORM_STOPPABLE_H

#pragma once

#include <future>

class Stoppable {
    std::promise<void> exit_signal_;
    std::future<void> future_object_;
public:
    Stoppable() :
            future_object_(exit_signal_.get_future()) {
    }

    Stoppable(Stoppable &&obj) : exit_signal_(std::move(obj.exit_signal_)), future_object_(std::move(obj.future_object_)) {
//        std::cout << "Move Constructor is called" << std::endl;
    }

    Stoppable &operator=(Stoppable &&obj) {
//        std::cout << "Move Assignment is called" << std::endl;
        exit_signal_ = std::move(obj.exit_signal_);
        future_object_ = std::move(obj.future_object_);
        return *this;
    }

    // Task need to provide defination  for this function
    // It will be called by thread function
    virtual void run() = 0;

    // Thread function to be executed by thread
    void operator()() {
        run();
    }

    //Checks if thread is requested to stop
    bool stopRequested() {
        // checks if value in future object is available
        if (future_object_.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout)
            return false;
        return true;
    }

    // Request the thread to stop by setting value in promise object
    void stop() {
        try {
            exit_signal_.set_value();
        } catch (const std::future_error& e) {
            if(e.code().value() == 2){
                // exit_signal_ already set
                // e.code() -> future:2
                // e.what():  std::future_error: Promise already satisfied
            } else{
                // something else ... pass it on
                throw;
            }
        }
    }
};

#endif //V2X_ROUTING_PLATFORM_STOPPABLE_H
