//
// Created by <Christoph Pilz> on 23.08.2021.
//
// Description:
// Parent interface describing a V2XInterfaceConnection
// used for logic V2X interface structure
//
// Author(s): "Christoph Pilz, Patrizia Neubauer, Loarda Tragaj"
// Copyright: "Copyright 2021, VIF V2X Platform Project"
// Credits: [""]
// License: "TBD"
// Version: "TBD"
// Maintainer: "Christoph Pilz"
// E-Mail: "christoph.pilz@v2c2.at"
// Status = "Production"
//
// Possible Improvements:
// [] Implement Priority Sending
// [] Implement replacement method for Logger*
// [] Check implementation of yield and sleep_for in run()
// [] Implement possibility to configure sleep times for the thread
// [] Check if logging influences performance
// [] Implement std::optional instead of std::experimental::optional when switching to C++17
// [] Implement sleep on signal for sending
// [] Implement sanity check in destructor for running threads, before delete
// [] Implement restartability -> check if run can be called, if everything was stopped with stop()
// [] Implement management of Rx/Tx Info (e.g. hops and security/SSP)
//

#ifndef V2X_ROUTING_PLATFORM_V2XINTERFACECONNECTION_H
#define V2X_ROUTING_PLATFORM_V2XINTERFACECONNECTION_H

#pragma once

#include <thread>
#include <utility>

//#include <optional> //C++17
#include <experimental/optional>

#include "util/ThreadsafeQueue.h"
#include "util/interfaces/NonAssignable.h"
#include "util/interfaces/Stoppable.h"
#include "util/logger/LoggingFacility.h"
#include "util/logger/ClassStandardOutputLogger.h"

class V2XInterfaceConnection : public Stoppable, public NonAssignable {
public:
    /// Constructor, sets the connection type
    V2XInterfaceConnection(std::string connection_type = "N/D", Logger::LogLevel log_level = Logger::LogLevel::WARN);

    ///Destructor
    virtual ~V2XInterfaceConnection();

    /// Returns the Connection Type
    /// \return connection_type_ ... std::string, N/D ... if not defined
    std::string ConnectionType();

    /// Connect the interface
    /// \return 0 ... Success, -1 ... Error
    virtual int32_t Connect() = 0;

    /// Close the interface
    /// \return 0 ... Success, -1 ... Error
    virtual int32_t Close() = 0;

    /// get V2X message from incoming queue
    /// \return V2X message received with port, as optional tuple
    std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> Receive();
    // std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> Receive(); //C++17

    /// put V2X message into outgoing queue
    /// \param outgoing_msg ... V2X message and port to send to
    void Send(std::tuple<std::pair<void *, size_t>, unsigned int> outgoing_msg);

    /// Default core thread method that handles receiving and sending threads
    void run() override;

protected:
    Logger *logger_;

    ThreadsafeQueue<std::tuple<std::pair<void *, size_t>, unsigned int>> incoming_msg_queue_;
    ThreadsafeQueue<std::tuple<std::pair<void *, size_t>, unsigned int>> outgoing_msg_queue_;

    /// receive V2X message
    /// \return V2X message and port, as optional tuple
    virtual std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> DoReceive() = 0;
    // virtual std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> doReceive() = 0; //C++17

    /// send V2X messages
    /// \param outgoing_msg ... V2X message to send to port
    virtual void DoSend(std::tuple<std::pair<void *, size_t>, unsigned int> outgoing_msg) = 0;

    /// Default receiving thread method
    virtual void RxThread();

    /// Default sending thread method
    virtual void TxThread();

private:
    std::string connection_type_;

    std::thread *rx_thread_;
    std::thread *tx_thread_;
};

#endif // V2X_ROUTING_PLATFORM_V2XINTERFACECONNECTION_H