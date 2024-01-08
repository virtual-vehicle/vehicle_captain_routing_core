//
// Created by <Christoph Pilz> on 25.08.2021.
//
// Description:
// Implementation of a Connection for the Unex ITS-G5 module
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
// [] use rx_info for further processing
// [] switch to C++17 if possible and change experimental::optional
// [] implement receiving/sending of rx/tx info data
// [] upgrade Unex ITS-G5 protocol and uncomment handler default value and uncomment init() in connect()
// [] implement sanity check in destructor -> be sure that Close() was used!
// [] timeloss @DoReceive(): PackLocalInfo(&rawRxMessage); ... it costs 1-2ms and 3 !seconds! if GNSS not available -> check on startup! ... also problematic for time measurements (highlight in report!)
// [] check "Caster RX timeout" -> do sth like: 10x 10-100ms timeout then switch do something for reconnect, or warn in 100-1000ms intervals
//

#ifndef V2X_ROUTING_PLATFORM_UNEXITSG5INTERFACECONNECTION_H
#define V2X_ROUTING_PLATFORM_UNEXITSG5INTERFACECONNECTION_H

#pragma once

#include "V2XInterfaceConnection.h"

#include <map>
#include <vector>

extern "C" {
#include "itsg5_sdk/eu_caster_service.h"
#include "itsg5_sdk/poti_caster_service.h"

#include "vcits/vccontainer/RawRxMessage.h"
#include "vcits/vccontainer/RawTxMessage.h"
}

class UnexITSG5InterfaceConnection : public V2XInterfaceConnection {
public:

    static const unsigned int SSP_LENGTH = 32U;
    static const unsigned int CASTER_CAM = 0U;
    static const unsigned int CASTER_DENM = 1U;
    static const unsigned int CASTER_MAPEM = 2U;
    static const unsigned int CASTER_SPATEM = 3U;
    static const unsigned int CASTER_IVIM = 4U;
    static const unsigned int CASTER_CPM = 5U;
    static const unsigned int CASTER_RTCMEM = 6U;
    static const unsigned int CASTER_VAM = 7U;
    static const unsigned int RX_MAX = 1500U;

    /// Constructor
    /// \param ip ... ip address for the Unex module
    /// \param btp_ports ... BTP ports that should be used
    /// \param log_level ... Logger::LogLevel (Default = NONE)
    UnexITSG5InterfaceConnection(std::string ip, std::vector<unsigned int> btp_ports, Logger::LogLevel log_level = Logger::LogLevel::WARN);

    /// Destructor warns on open connections
    virtual ~UnexITSG5InterfaceConnection();

    /// Connect the interface
    /// \return 0 ... Success, -1 ... Error
    int32_t Connect() override;

    /// Close the interface
    /// \return 0 ... Success, -1 ... Error
    int32_t Close() override;

protected:
    /// Creates an instance of Rx Caster
    void CreateRxCaster();
    /// Creates an instance of Tx Caster
    void CreateTxCaster();
    /// Releases and cleans up the Rx Caster instance
    void ReleaseRxCaster();
    /// Releases and cleans up the Tx Caster instance
    void ReleaseTxCaster();

    /// Overrides the RxThread() method from parent class V2XInterfaceConnection
    void RxThread() override;

    /// Overrides the TxThread() method from parent class V2XInterfaceConnection
    void TxThread() override;


    /// receive V2X message
    /// \return V2X message and port, as optional tuple
    std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> DoReceive() override;
    // std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> DoReceive() override; //C++17

    /// send V2X messages
    /// \param outgoing_msg ... V2X message and port to send to
    void DoSend(std::tuple<std::pair<void *, size_t>, unsigned int> outgoing_msg) override;

private:
    std::string ip_;
    std::vector<unsigned int> btp_ports_;

    // caster handler for each port
    std::map<unsigned int, caster_comm_config_t> rx_config;
    std::map<unsigned int, caster_comm_config_t> tx_config;
    std::map<unsigned int, caster_handler_t > rx_handler_;  // = EU_INVALID_CASTER_HANDLER;
    std::map<unsigned int, caster_handler_t > tx_handler_;  // = EU_INVALID_CASTER_HANDLER;

    // poti handler
    caster_comm_config_t poti_config;
    caster_handler_t rx_poti_handler_; // = POTI_INVALID_CASTER_HANDLER;
    caster_handler_t tx_poti_handler_; // = POTI_INVALID_CASTER_HANDLER;

    // packing methods
    /// pack the current time and geo location
    /// WARNING: do not use, takes up to 3s when no GNSS available -> should be filled by routing (message enhancement)
    /// \param rawRxMessage [out] the rawMxMessage with filled LocalInfo
    void PackLocalInfo(RawRxMessage *rawRxMessage);

    /// pack the rx info into the raw message
    /// \param rawRxMessage [out] the rawRxMessage with filled rx info
    /// \param rx_info [in] the received rx info
    void PackRxInfo(RawRxMessage *rawRxMessage, eu_caster_rx_info_t *rx_info);

    // debug methods
    /// dumping method for debugging Rx
    void dumpRxInfo_(eu_caster_rx_info_t *rx_info);
};

#endif // V2X_ROUTING_PLATFORM_UNEXITSG5INTERFACECONNECTION_H