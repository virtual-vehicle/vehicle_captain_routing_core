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

#include "V2XDefines.h"

// --- --- Public --- ---
const unsigned int V2XDefines::BTP_PORT_NONE = 0U;
const unsigned int V2XDefines::BTP_PORT_CA = 2001U;
const unsigned int V2XDefines::BTP_PORT_DEN = 2002U;
const unsigned int V2XDefines::BTP_PORT_RLT = 2003U;
const unsigned int V2XDefines::BTP_PORT_TLM = 2004U;
const unsigned int V2XDefines::BTP_PORT_SA = 2005U;
const unsigned int V2XDefines::BTP_PORT_IVI = 2006U;
const unsigned int V2XDefines::BTP_PORT_TLC1 = 2007U;
const unsigned int V2XDefines::BTP_PORT_TLC2 = 2008U;
//const unsigned int V2XDefines::BTP_PORT_CP = 2009U;
const unsigned int V2XDefines::BTP_PORT_CP = 2001U;
const unsigned int V2XDefines::BTP_PORT_POI = 2010U;
const unsigned int V2XDefines::BTP_PORT_TPG = 2011U;
const unsigned int V2XDefines::BTP_PORT_CHARGING = 2012U;
const unsigned int V2XDefines::BTP_PORT_GPC = 2013U;
const unsigned int V2XDefines::BTP_PORT_CTL = 2014U;
const unsigned int V2XDefines::BTP_PORT_CRL = 2015U;
const unsigned int V2XDefines::BTP_PORT_CERT_REQUEST = 2016U;
const unsigned int V2XDefines::BTP_PORT_MCD = 2017U;
//const unsigned int V2XDefines::BTP_PORT_VA = 2018U;
const unsigned int V2XDefines::BTP_PORT_VA = 2001U;
const unsigned int V2XDefines::BTP_PORT_IMZ = 2019U;


const unsigned int V2XDefines::MSG_ID_NONE = 0U;
const unsigned int V2XDefines::MSG_ID_DENM = 1U;
const unsigned int V2XDefines::MSG_ID_CAM = 2U;
const unsigned int V2XDefines::MSG_ID_POI = 3U;
const unsigned int V2XDefines::MSG_ID_SPATEM = 4U;
const unsigned int V2XDefines::MSG_ID_MAPEM = 5U;
const unsigned int V2XDefines::MSG_ID_IVIM = 6U;
const unsigned int V2XDefines::MSG_ID_EV_RSR = 7U;
const unsigned int V2XDefines::MSG_ID_TISTPGTRANSACTION = 8U;
const unsigned int V2XDefines::MSG_ID_SREM = 9U;
const unsigned int V2XDefines::MSG_ID_SSEM = 10U;
const unsigned int V2XDefines::MSG_ID_EVCSN = 11U;
const unsigned int V2XDefines::MSG_ID_SAEM = 12U;
const unsigned int V2XDefines::MSG_ID_RTCMEM = 13U;
const unsigned int V2XDefines::MSG_ID_CPM = 14U;
const unsigned int V2XDefines::MSG_ID_VAM = 102U;
const unsigned int V2XDefines::MSG_ID_UNKNOWN = -1U;

std::map<std::string, unsigned int> V2XDefines::V2X_ID_FROM_MSG = {
        {"denm", MSG_ID_DENM},
        {"cam", MSG_ID_CAM},
        {"poi", MSG_ID_POI},
        {"spatem", MSG_ID_SPATEM},
        {"mapem", MSG_ID_MAPEM},
        {"ivim", MSG_ID_IVIM},
        {"ev_rsr", MSG_ID_EV_RSR},
        {"tistpgtransaction", MSG_ID_TISTPGTRANSACTION},
        {"srem", MSG_ID_SREM},
        {"ssem", MSG_ID_SSEM},
        {"evcsn", MSG_ID_EVCSN},
        {"saem", MSG_ID_SAEM},
        {"rtcmem", MSG_ID_RTCMEM},
        {"cpm", MSG_ID_CPM},
        {"vam", MSG_ID_VAM},
        {"unknown", MSG_ID_UNKNOWN}
};
std::map<unsigned int, std::string> V2XDefines::V2X_MSG_FROM_ID = {
        {MSG_ID_DENM, "denm"},
        {MSG_ID_CAM, "cam"},
        {MSG_ID_POI, "poi"},
        {MSG_ID_SPATEM, "spatem"},
        {MSG_ID_MAPEM, "mapem"},
        {MSG_ID_IVIM, "ivim"},
        {MSG_ID_EV_RSR, "ev_rsr"},
        {MSG_ID_TISTPGTRANSACTION, "tistpgtransaction"},
        {MSG_ID_SREM, "srem"},
        {MSG_ID_SSEM, "ssem"},
        {MSG_ID_EVCSN, "evcsn"},
        {MSG_ID_SAEM, "saem"},
        {MSG_ID_RTCMEM, "rtcmem"},
        {MSG_ID_CPM, "cpm"},
        {MSG_ID_VAM, "vam"},
        {MSG_ID_UNKNOWN, "unknown"}
};

std::map<std::string, unsigned int> V2XDefines::BTP_PORT_ID_FROM_NAME = {
        {"CA", BTP_PORT_CA},
        {"DEN", BTP_PORT_DEN},
        {"RLT", BTP_PORT_RLT},
        {"TLM", BTP_PORT_TLM},
        {"SA", BTP_PORT_SA},
        {"IVI", BTP_PORT_IVI},
        {"TLC1", BTP_PORT_TLC1},
        {"TLC2", BTP_PORT_TLC2},
        {"CP", BTP_PORT_CP},
        {"POI", BTP_PORT_POI},
        {"TPG", BTP_PORT_TPG},
        {"CHARGING", BTP_PORT_CHARGING},
        {"GPC", BTP_PORT_GPC},
        {"CTL", BTP_PORT_CTL},
        {"CRL", BTP_PORT_CRL},
        {"CERT_REQUEST", BTP_PORT_CERT_REQUEST},
        {"MCD", BTP_PORT_MCD},
        {"VA", BTP_PORT_VA},
        {"IMZ", BTP_PORT_IMZ}
};
std::map<unsigned int, std::string> V2XDefines::BTP_PORT_NAME_FROM_ID = {
        {BTP_PORT_CA, "CA"},
        {BTP_PORT_DEN, "DEN"},
        {BTP_PORT_RLT, "RLT"},
        {BTP_PORT_TLM, "TLM"},
        {BTP_PORT_SA, "SA"},
        {BTP_PORT_IVI, "IVI"},
        {BTP_PORT_TLC1, "TLC1"},
        {BTP_PORT_TLC2, "TLC2"},
        {BTP_PORT_CP, "CP"},
        {BTP_PORT_POI, "POI"},
        {BTP_PORT_TPG, "TPG"},
        {BTP_PORT_CHARGING, "CHARGING"},
        {BTP_PORT_GPC, "GPC"},
        {BTP_PORT_CTL, "CTL"},
        {BTP_PORT_CRL, "CRL"},
        {BTP_PORT_CERT_REQUEST, "CERT_REQUEST"},
        {BTP_PORT_MCD, "MCD"},
        {BTP_PORT_VA, "VA"},
        {BTP_PORT_IMZ, "IMZ"}
};
