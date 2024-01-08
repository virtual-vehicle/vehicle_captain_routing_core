//
// Created by Christoph Pilz on 02.12.2021.
//
// Description:
// This Class is a Lightweight Implementation on ZMQ routing.
// It gets raw messages from the local ZMQ socket and puts them on the remote ZMQ socket and vice versa.
// It also extracts the V2X payload from the raw messages and distributes it to respective ZMQ channels
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
// Reference to used code:
// <Description1 what was used> (<Link>)
// <Description2 what was used> (<Link>)
//
// Possible Improvements:
// [] add description in boilerplate
// [] add triple-/ comments for documentation of methods
// []
//

#ifndef V2X_ROUTING_PLATFORM_LIGHTWEIGHTZMQROUTINGCONTROL_H
#define V2X_ROUTING_PLATFORM_LIGHTWEIGHTZMQROUTINGCONTROL_H

#include "BaseZmqRoutingControl.h"

class LightWeightZmqRoutingControl : public BaseZmqRoutingControl {
public:
    LightWeightZmqRoutingControl(
            std::string envelope_raw_prefix,
            std::string envelope_v2x_prefix,
            int cycle_time_ms = 0,
            std::string v2x_routing_control_type = "LightWeightZmqRoutingControl",
            Logger::LogLevel log_level = Logger::LogLevel::WARN);

    virtual ~LightWeightZmqRoutingControl();

protected:
//    /// take v2x messages from remote, convert it to raw message type and send it to local
//    void RunRemoteLocal() override;

    /// take raw message from local, send it to remote; also take only v2x payload and send via respective channel
    virtual void RunLocalRemote() override;

    /// simply takes the messages from the remote socket and sends it to local
    virtual void RunRemoteLocal() override;

private:
    std::string envelope_raw_prefix_;
    std::string envelope_v2x_prefix_;

    /// extract the asn1 v2x message payload from the raw asn1 message
    /// \param extracted_message asn1 message payload
    /// \param msg raw asn1 msg
    void ExtractV2XMessage(zmq::message_t &extracted_message, zmq::message_t &msg);

    /// Get the message ID of a given V2X message
    /// \param msg with V2X content to get ID from
    /// \return V2X message ID
    unsigned int GetV2XMessageID(zmq::message_t &msg);
};

#endif //V2X_ROUTING_PLATFORM_LIGHTWEIGHTZMQROUTINGCONTROL_H
