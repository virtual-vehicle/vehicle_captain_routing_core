// -*- lsst-c++ -*-

/*
* VIF V2X Platform
* See COPYRIGHT file at the top of the source tree.
*
* This product includes software developed by the
* InSecTT Project (https://www.insectt.eu/).
*
* (Licensing)
* TBD
*/

#include "V2XInterfaceConnection.h"

// --- --- Public --- ---

V2XInterfaceConnection::V2XInterfaceConnection(std::string connection_type, Logger::LogLevel log_level) {
    connection_type_ = connection_type;
    logger_ = new ClassStandardOutputLogger(log_level, connection_type_);
    rx_thread_ = nullptr;
    tx_thread_ = nullptr;
}

V2XInterfaceConnection::~V2XInterfaceConnection() {
    delete tx_thread_;
    delete rx_thread_;
    delete logger_;
}

std::string V2XInterfaceConnection::ConnectionType() {
    return connection_type_;
}

std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> V2XInterfaceConnection::Receive() {
    return incoming_msg_queue_.pop();
}

void V2XInterfaceConnection::Send(std::tuple<std::pair<void *, size_t>, unsigned int> outgoing_msg) {
    outgoing_msg_queue_.push(outgoing_msg);
}

void V2XInterfaceConnection::run() {
    logger_->WriteInfoEntry("run()");

    if (rx_thread_ == nullptr) {
        rx_thread_ = new std::thread(&V2XInterfaceConnection::RxThread, this);
    } else {
        logger_->WriteWarnEntry("run(): RxThread might be already running");
    }

    if (tx_thread_ == nullptr) {
        tx_thread_ = new std::thread(&V2XInterfaceConnection::TxThread, this);
    } else {
        logger_->WriteWarnEntry("run(): TxThread might be already running");
    }

    logger_->WriteInfoEntry("run(): end");
}

// --- --- Protected --- ---

void V2XInterfaceConnection::RxThread() {
    logger_->WriteInfoEntry("RxThread()");

    while (!stopRequested()) {
        logger_->WriteTraceEntry("RxThread(): loop start");

        // receive
        // std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> msg = DoReceive(); //C++17
        std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> msg = DoReceive();

        if (msg) {
            logger_->WriteTraceEntry("RxThread(): msg received");
            incoming_msg_queue_.push(msg.value());
            std::this_thread::yield();
        } else {
            // if there is no message, do polling
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); //1000Hz
        }
    }

    logger_->WriteInfoEntry("RxThread(): end");
}

void V2XInterfaceConnection::TxThread() {
    logger_->WriteInfoEntry("TxThread()");

    // Check if thread is requested to stop?
    while (!stopRequested()) {
        logger_->WriteTraceEntry("TxThread(): loop start");

        //send
        // std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> msg = outgoing_msg_queue_.pop(); //C++17
        std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> msg = outgoing_msg_queue_.pop();
        if (msg) {
            logger_->WriteTraceEntry("TxThread(): msg to send");
            DoSend(msg.value());
            std::this_thread::yield();
        } else {
            // if there is no message, do polling
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); //1000Hz
        }
    }

    logger_->WriteInfoEntry("TxThread(): end");
}
