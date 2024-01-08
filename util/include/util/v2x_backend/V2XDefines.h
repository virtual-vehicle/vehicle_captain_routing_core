//
// Created by Christoph Pilz on 11.08.2022.
//
// Description:
// TBA
//
// Author(s): "Christoph Pilz"
// Copyright: "Copyright 2022, VIF V2X Platform Project"
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
// []
//

#ifndef V2X_ROUTING_PLATFORM_V2XDEFINES_H
#define V2X_ROUTING_PLATFORM_V2XDEFINES_H

#include <map>
#include <string>

#include "NonAssignable.h"

class V2XDefines : public NonAssignable {
public:
    static const unsigned int BTP_PORT_NONE;
    static const unsigned int BTP_PORT_CA;
    static const unsigned int BTP_PORT_DEN;
    static const unsigned int BTP_PORT_RLT;
    static const unsigned int BTP_PORT_TLM;
    static const unsigned int BTP_PORT_SA;
    static const unsigned int BTP_PORT_IVI;
    static const unsigned int BTP_PORT_TLC1;
    static const unsigned int BTP_PORT_TLC2;
    static const unsigned int BTP_PORT_CP;
    static const unsigned int BTP_PORT_POI;
    static const unsigned int BTP_PORT_TPG;
    static const unsigned int BTP_PORT_CHARGING;
    static const unsigned int BTP_PORT_GPC;
    static const unsigned int BTP_PORT_CTL;
    static const unsigned int BTP_PORT_CRL;
    static const unsigned int BTP_PORT_CERT_REQUEST;
    static const unsigned int BTP_PORT_MCD;
    static const unsigned int BTP_PORT_VA;
    static const unsigned int BTP_PORT_IMZ;

    static const unsigned int MSG_ID_NONE;
    static const unsigned int MSG_ID_DENM;
    static const unsigned int MSG_ID_CAM;
    static const unsigned int MSG_ID_POI;
    static const unsigned int MSG_ID_SPATEM;
    static const unsigned int MSG_ID_MAPEM;
    static const unsigned int MSG_ID_IVIM;
    static const unsigned int MSG_ID_EV_RSR;
    static const unsigned int MSG_ID_TISTPGTRANSACTION;
    static const unsigned int MSG_ID_SREM;
    static const unsigned int MSG_ID_SSEM;
    static const unsigned int MSG_ID_EVCSN;
    static const unsigned int MSG_ID_SAEM;
    static const unsigned int MSG_ID_RTCMEM;
    static const unsigned int MSG_ID_CPM;
    static const unsigned int MSG_ID_VAM;
    static const unsigned int MSG_ID_UNKNOWN;

    static std::map<std::string, unsigned int> V2X_ID_FROM_MSG;
    static std::map<unsigned int, std::string> V2X_MSG_FROM_ID;

    static std::map<std::string, unsigned int> BTP_PORT_ID_FROM_NAME;
    static std::map<unsigned int, std::string> BTP_PORT_NAME_FROM_ID;

    V2XDefines() = delete;

    ~V2XDefines() = delete;

};

#endif //V2X_ROUTING_PLATFORM_V2XDEFINES_H
