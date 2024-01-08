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

#include "UnexITSG5InterfaceConnection.h"

#include <cmath>
#include <ctime>
#include <csignal>
#include <cstring>

#include "util/v2x_backend/V2XDefines.h"

extern "C" {
#include "itsg5_sdk/error_code_enum.h"
#include "itsg5_sdk/error_code_user.h"
#include "itsg5_sdk/eu_caster_service.h"
#include "itsg5_sdk/itsmsg_codec.h"

#include "vcits/parser/Encoder.h"
#include "vcits/vccontainer/LocalInfo.h"
#include "vcits/vccontainer/RawRxMessage.h"
#include "vcits/vccontainer/RawTxMessage.h"
}

// --- --- Public --- ---

UnexITSG5InterfaceConnection::UnexITSG5InterfaceConnection(std::string ip, std::vector<unsigned int> btp_ports,
                                                           Logger::LogLevel log_level)
        : V2XInterfaceConnection(std::string("UnexITSG5InterfaceConnection-") + ip, log_level) {
    ip_ = ip;
    btp_ports_ = btp_ports;
}

UnexITSG5InterfaceConnection::~UnexITSG5InterfaceConnection() {
}

int32_t UnexITSG5InterfaceConnection::Connect() {
    logger_->WriteInfoEntry("Connect()");

    /* local variables */
    poti_config = {.ip = ip_.c_str(), .caster_id = 0, .caster_comm_mode = CASTER_MODE_POTI};

    /* communication config */
    for (unsigned int btp_port: btp_ports_) {
        if (btp_port == V2XDefines::BTP_PORT_CA) {
            logger_->WriteTraceEntry("V2XDefines::BTP_PORT_CA");
            rx_config[V2XDefines::BTP_PORT_CA] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_CAM, .caster_comm_mode = CASTER_MODE_RX};
            tx_config[V2XDefines::BTP_PORT_CA] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_CAM, .caster_comm_mode = CASTER_MODE_TX};
        } else if (btp_port == V2XDefines::BTP_PORT_DEN) {
            logger_->WriteTraceEntry("V2XDefines::BTP_PORT_DEN");
            rx_config[V2XDefines::BTP_PORT_DEN] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_DENM, .caster_comm_mode = CASTER_MODE_RX};
            tx_config[V2XDefines::BTP_PORT_DEN] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_DENM, .caster_comm_mode = CASTER_MODE_TX};
        } else if (btp_port == V2XDefines::BTP_PORT_RLT) {
            logger_->WriteTraceEntry("V2XDefines::BTP_PORT_RLT");
            rx_config[V2XDefines::BTP_PORT_RLT] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_MAPEM, .caster_comm_mode = CASTER_MODE_RX};
            tx_config[V2XDefines::BTP_PORT_RLT] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_MAPEM, .caster_comm_mode = CASTER_MODE_TX};
        } else if (btp_port == V2XDefines::BTP_PORT_TLM) {
            logger_->WriteTraceEntry("V2XDefines::BTP_PORT_TLM");
            rx_config[V2XDefines::BTP_PORT_TLM] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_SPATEM, .caster_comm_mode = CASTER_MODE_RX};
            tx_config[V2XDefines::BTP_PORT_TLM] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_SPATEM, .caster_comm_mode = CASTER_MODE_TX};
        } else if (btp_port == V2XDefines::BTP_PORT_IVI) {
            logger_->WriteTraceEntry("V2XDefines::BTP_PORT_IVI");
            rx_config[V2XDefines::BTP_PORT_IVI] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_IVIM, .caster_comm_mode = CASTER_MODE_RX};
            tx_config[V2XDefines::BTP_PORT_IVI] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_IVIM, .caster_comm_mode = CASTER_MODE_TX};
        } else if (btp_port == V2XDefines::BTP_PORT_CP) {
            logger_->WriteTraceEntry("V2XDefines::BTP_PORT_CP");
            rx_config[V2XDefines::BTP_PORT_CP] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_CPM, .caster_comm_mode = CASTER_MODE_RX};
            tx_config[V2XDefines::BTP_PORT_CP] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_CPM, .caster_comm_mode = CASTER_MODE_TX};
        } else if (btp_port == V2XDefines::BTP_PORT_GPC) {
            logger_->WriteTraceEntry("V2XDefines::BTP_PORT_GPC");
            rx_config[V2XDefines::BTP_PORT_GPC] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_RTCMEM, .caster_comm_mode = CASTER_MODE_RX};
            tx_config[V2XDefines::BTP_PORT_GPC] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_RTCMEM, .caster_comm_mode = CASTER_MODE_TX};
        } else if (btp_port == V2XDefines::BTP_PORT_VA) {
            logger_->WriteTraceEntry("V2XDefines::BTP_PORT_VA");
            rx_config[V2XDefines::BTP_PORT_VA] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_VAM, .caster_comm_mode = CASTER_MODE_RX};
            tx_config[V2XDefines::BTP_PORT_VA] = {.ip = ip_.c_str(), .caster_id = UnexITSG5InterfaceConnection::CASTER_VAM, .caster_comm_mode = CASTER_MODE_TX};
        } else {
            logger_->WriteWarnEntry("Connect(): unsupported btp_port (" + std::to_string(btp_port) +
                                    ") ... will do nothing ... might lead to problems");
        }
    }

    return 0;
}

int32_t UnexITSG5InterfaceConnection::Close() {
    logger_->WriteInfoEntry("Close()");
    eu_caster_deinit();
    return 0;
}

// --- --- Protected --- ---

// std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> UnexITSG5InterfaceConnection::DoReceive() override; //C++17
std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> UnexITSG5InterfaceConnection::DoReceive() {
    logger_->WriteTraceEntry("DoReceive()");

    /* local variables */
    void *rawRxMessageStream = nullptr;
    uint8_t rx_buf[RX_MAX];
    size_t len = 0;
    ssize_t rawRxMessageStreamSize = 0;
    ssize_t buf_size = sizeof(rx_buf);
    eu_caster_rx_info_t rx_info;
    int ret;
    // std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> msg; //C++17
    std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> msg;
    RawRxMessage rawRxMessage;

    /* initialize variables */
    // initialize message with 0
    std::memset((void *) &rawRxMessage, 0, sizeof(rawRxMessage));

    for (unsigned int btp_port: btp_ports_) {
        ret = eu_caster_rx_timeout(rx_handler_[btp_port], &rx_info, rx_buf, buf_size, &len, 0);

        if (IS_SUCCESS(ret)) {
            logger_->WriteDebugEntry("DoReceive(): received " + std::to_string(len) + " bytes!");

            /* Pack Time and GeoData at time of reception */
            // Not recommended for use -> takes up to 3s, when no GNSS available. Move LocalInfo Packing to routing
            // PackLocalInfo(&rawRxMessage);

            /* Pack ITS-G5 RX information into raw message */
            PackRxInfo(&rawRxMessage, &rx_info);

            /* Put received msg into payload */
            rawRxMessage.payloadSize = len;
            rawRxMessage.payloadString = static_cast<OCTET_STRING_t *>(std::malloc(sizeof(OCTET_STRING_t)));
            std::memset(static_cast<void *>(rawRxMessage.payloadString), 0, sizeof(OCTET_STRING_t));

            if (rawRxMessage.payloadString == nullptr) {
                logger_->WriteFatalEntry("DoReceive(): malloc failed ... out of memory?");
            }

            OCTET_STRING_fromBuf(rawRxMessage.payloadString, reinterpret_cast<char *>(rx_buf), len);

            /* validate and convert RawRxMessage to ASN.1 stream and create a tuple */
            Encoder::validate_constraints(&asn_DEF_RawRxMessage, &rawRxMessage);
            rawRxMessageStreamSize = Encoder::encode(&asn_DEF_RawRxMessage, nullptr, &rawRxMessage,
                                                     &rawRxMessageStream);

            // msg = std::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> {std::make_tuple(v2x_asn1_stream, len)}; //C++17
            msg = std::experimental::make_optional(
                    std::make_tuple(std::make_pair(rawRxMessageStream, rawRxMessageStreamSize), btp_port));

            // received message: highest priority BTP wins
            break;
        } else {
            /* handle error */
            switch (ret) {
                case ERROR_V2XCAST_CASTER_RX_TIMEOUT:
                    // intended behavior if there is no message
                    logger_->WriteTraceEntry("DoReceive(): intended behavior, clear timeout");
                    break;
                case ERROR_V2XCAST_CASTER_RX_FAIL_THREAD_ID_MISMTACH:
                    logger_->WriteErrorEntry("DoReceive(): bad state, threading problem, this should not happen ("
                                                + std::string(ERROR_MSG(ret))
                                                + ")");
                    break;
                default:
                    logger_->WriteErrorEntry("Failed to receive data, error code is: "
                                                + std::to_string(ret)
                                                + ": "
                                                + std::string(ERROR_MSG(ret))
                                                + ")");
            }

            // msg = std::nullopt; //C++17
            msg = std::experimental::nullopt;
        }
    }

    return msg;
}

void UnexITSG5InterfaceConnection::DoSend(std::tuple<std::pair<void *, size_t>, unsigned int> outgoing_msg) {
    logger_->WriteTraceEntry("DoSend()");
    int ret;

    ret = eu_caster_tx(tx_handler_[std::get<1>(outgoing_msg)],
                       nullptr,
                       static_cast<uint8_t *>(std::get<0>(outgoing_msg).first),
                       static_cast<int>(std::get<0>(outgoing_msg).second));

    if (IS_SUCCESS(ret)) {
        logger_->WriteTraceEntry("DoSend(): V2X message sent");
    } else {
        logger_->WriteWarnEntry("DoSend(): V2X sending failed");
    }

    std::free(std::get<0>(outgoing_msg).first);
    return;
}

void UnexITSG5InterfaceConnection::CreateRxCaster() {
    logger_->WriteInfoEntry("CreateRxCaster()");

    /* local variables */
    int ret_rx;

    eu_caster_init();

    /* create EU caster */
    for (unsigned int btp_port: btp_ports_) {
        ret_rx = eu_caster_create(&rx_handler_[btp_port], &rx_config[btp_port]);

        if (IS_SUCCESS(ret_rx)) {
            logger_->WriteInfoEntry("CreateRxCaster(): RX caster connect successful (" + ip_ + ", " + std::to_string(btp_port) + ")");
        } else {
            logger_->WriteErrorEntry("CreateRxCaster(): RX connect error " + std::to_string(ret_rx) + ": " + std::string(error_msg(ret_rx)) + ", ");
        }
    }

    /* create POTI caster */
    ret_rx = eu_caster_create(&rx_poti_handler_, &poti_config);

    if (IS_SUCCESS(ret_rx)) {
        logger_->WriteInfoEntry("CreateRxCaster(): RX POTI caster connect successful (" + ip_ + ")");
    } else {
        logger_->WriteErrorEntry("CreateRxCaster(): RX POTI connect error " + std::to_string(ret_rx) + ": " + std::string(error_msg(ret_rx)) + ", ");
    }
}

void UnexITSG5InterfaceConnection::CreateTxCaster() {
    logger_->WriteInfoEntry("CreateTxCaster()");

    /* local variables */
    int ret_tx;

    eu_caster_init();

    /* create EU caster */
    for (unsigned int btp_port: btp_ports_) {
        ret_tx = eu_caster_create(&tx_handler_[btp_port], &tx_config[btp_port]);

        if (IS_SUCCESS(ret_tx)) {
            logger_->WriteInfoEntry("CreateTxCaster(): TX caster connect successful (" + ip_ + ", " + std::to_string(btp_port) + ")");
        } else {
            logger_->WriteErrorEntry("CreateTxCaster(): TX connect error " + std::to_string(ret_tx) + ": " + std::string(error_msg(ret_tx)));
        }
    }

    /* create POTI caster */
    ret_tx = eu_caster_create(&tx_poti_handler_, &poti_config);

    if (IS_SUCCESS(ret_tx)) {
        logger_->WriteInfoEntry("CreateTxCaster(): TX POTI caster connect successful (" + ip_ + ")");
    } else {
        logger_->WriteErrorEntry("CreateTxCaster(): TX POTI connect error " + std::to_string(ret_tx) + ": " + std::string(error_msg(ret_tx)));
    }
}

void UnexITSG5InterfaceConnection::ReleaseRxCaster() {
    logger_->WriteInfoEntry("ReleaseRxCaster()");

    /* local variables */
    int ret_rx;

    /* release the caster */
    for (unsigned int btp_port: btp_ports_) {
        ret_rx = eu_caster_release(rx_handler_[btp_port]);

        if (IS_SUCCESS(ret_rx)) {
            logger_->WriteInfoEntry("ReleaseRxCaster(): RX caster release successful (" + ip_ + ", " + std::to_string(btp_port) +")");
        } else {
            logger_->WriteErrorEntry("ReleaseRxCaster(): RX close error " + std::to_string(ret_rx) + ": " + std::string(error_msg(ret_rx)) + ", ");
        }
    }
}

void UnexITSG5InterfaceConnection::ReleaseTxCaster() {
    logger_->WriteInfoEntry("ReleaseTxCaster()");

    /* local variables */
    int ret_tx;

    /* release the caster */
    for (unsigned int btp_port: btp_ports_) {
        ret_tx = eu_caster_release(tx_handler_[btp_port]);

        if (IS_SUCCESS(ret_tx)) {
            logger_->WriteInfoEntry("ReleaseTxCaster(): TX caster release successful (" + ip_ + ", " + std::to_string(btp_port) + ")");
        } else {
            logger_->WriteErrorEntry("ReleaseTxCaster(): TX close error " + std::to_string(ret_tx) + ": " + std::string(error_msg(ret_tx)));
        }
    }
}

void UnexITSG5InterfaceConnection::RxThread() {
    logger_->WriteInfoEntry("RxThread():");

    // Unex would recommend setting the thread priority (API example: app_set_thread_name_and_priority)

    CreateRxCaster();

    while (stopRequested() == false) {
        logger_->WriteTraceEntry("RxThread(): loop start");
        std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> msg = DoReceive();

        if (msg) {
            logger_->WriteTraceEntry("RxThread(): msg received");
            incoming_msg_queue_.push(msg.value());

            std::this_thread::yield();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); //1000Hz
        }
    }

    ReleaseRxCaster();
    logger_->WriteInfoEntry("RxThread(): end");
}

void UnexITSG5InterfaceConnection::TxThread() {
    logger_->WriteInfoEntry("TxThread()");

    // Unex would recommend setting the thread priority (API example: app_set_thread_name_and_priority)

    CreateTxCaster();

    while (stopRequested() == false) {
        logger_->WriteTraceEntry("TxThread(): loop start");
        std::experimental::optional<std::tuple<std::pair<void *, size_t>, unsigned int>> msg = outgoing_msg_queue_.pop();

        if (msg) {
            logger_->WriteTraceEntry("TxThread(): msg to send");
            DoSend(msg.value());

            std::this_thread::yield();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); //1000Hz
        }
    }

    ReleaseTxCaster();
    logger_->WriteInfoEntry("TxThread(): end");
}

// --- --- Private --- ---

void UnexITSG5InterfaceConnection::PackLocalInfo(RawRxMessage *rawRxMessage) {
    logger_->WriteTraceEntry("PackLocalInfo()");

    /* variables */
    int ret;
    poti_fix_data_t fix_data;
    poti_gnss_info_t gnss_info;
    struct tm timestamp_utc;
    time_t timestamp;

    /* init struct with zeroes*/
    std::memset(&fix_data, 0, sizeof(fix_data));
    std::memset(&gnss_info, 0, sizeof(gnss_info));
    std::memset(&timestamp_utc, 0, sizeof(timestamp_utc));

    /* Get GNSS fix data from POTI caster service */
    //OPTIMIZE: timeout = 3s, calculation time 180ms in 10Hz mode
    //sth like this: https://stackoverflow.com/questions/40550730/how-to-implement-timeout-for-function-in-c
    ret = poti_caster_fix_data_get(rx_poti_handler_, &fix_data);

    if (ret != 0) {
        logger_->WriteDebugEntry("PackLocalInfo(): Failed to receive GNSS fix data from POTI caster service");
        return;
    } else if (fix_data.mode < POTI_FIX_MODE_2D) {
        logger_->WriteDebugEntry("PackLocalInfo(): GNSS not fixed, fix mode: " + std::to_string(fix_data.mode));
        /* Optional, APIs for users to get more GNSS information */
        ret = poti_caster_gnss_info_get(rx_poti_handler_, &gnss_info);
        if (IS_SUCCESS(ret)) {
            logger_->WriteTraceEntry("PackLocalInfo(): GNSS antenna status: " + std::to_string(gnss_info.antenna_status) +
                    ", time sync status: " + std::to_string(gnss_info.time_sync_status));
        }
        return;
    }

    /* Optional, NAN value check for GNSS data */
    if (std::isnan(fix_data.latitude) || std::isnan(fix_data.longitude) || std::isnan(fix_data.altitude) ||
        std::isnan(fix_data.horizontal_speed) || std::isnan(fix_data.course_over_ground)) {
        logger_->WriteDebugEntry("PackLocalInfo(): GNSS fix data has NAN value, latitude: " + std::to_string(fix_data.latitude) +
                ", longitude : " + std::to_string(fix_data.longitude) + ", altitude : " +
                std::to_string(fix_data.altitude) + ", horizontal speed : " +
                std::to_string(fix_data.horizontal_speed) + ", course over ground : " +
                std::to_string(fix_data.course_over_ground));
        return;
    }

    /* probably possible in new SDK 1.9 */
    // ret = poti_caster_gnss_info_get(rx_poti_handler_, &gnss_info);
    // if (IS_SUCCESS(ret)) {
    //     printf("Access layer time sync state: %d , unsync times: %d\n", gnss_info.acl_time_sync_state, gnss_info.acl_unsync_times);
    // }

    /* create OPTIONAL LocalInfo */
    rawRxMessage->localInfo = static_cast<LocalInfo *>(std::malloc(sizeof(LocalInfo)));
    if (rawRxMessage->localInfo == nullptr) {
        logger_->WriteFatalEntry("PackLocalInfo(): malloc failed ... out of memory?");
        std::raise(SIGABRT); // out of memory might already cause crash with logger ... trying to go for a "safe" exit
        return;
    }

    /* start packing */
    timestamp_utc.tm_sec = fix_data.time.utc.sec;
    timestamp_utc.tm_min = fix_data.time.utc.min;
    timestamp_utc.tm_hour = fix_data.time.utc.hour;
    timestamp_utc.tm_mday = fix_data.time.utc.mday;
    timestamp_utc.tm_mon = fix_data.time.utc.mon - 1;           // months since january 0-11
    timestamp_utc.tm_year = fix_data.time.utc.year - 1900;      // years since 1900
    timestamp = std::mktime(&timestamp_utc);

    rawRxMessage->localInfo->timestamp.sec = timestamp;
    rawRxMessage->localInfo->timestamp.usec = fix_data.time.utc.ms * 1000;
    rawRxMessage->localInfo->positionInfo.latitude = static_cast<long>(fix_data.latitude * 10000000.0);     // convert to 1/10 micro degree
    rawRxMessage->localInfo->positionInfo.longitude = static_cast<long>(fix_data.longitude * 10000000.0);   // convert to 1/10 micro degree

    return;
}

void UnexITSG5InterfaceConnection::PackRxInfo(RawRxMessage *rawRxMessage, eu_caster_rx_info_t *rx_info) {
    logger_->WriteTraceEntry("PackRxInfo()");

    /* just some packing to be done */
    rawRxMessage->rxInfo.timestamp.sec = rx_info->timestamp.tv_sec;
    rawRxMessage->rxInfo.timestamp.usec = rx_info->timestamp.tv_usec;
    rawRxMessage->rxInfo.rssi = rx_info->rssi;
    rawRxMessage->rxInfo.dataRate = rx_info->data_rate;
    rawRxMessage->rxInfo.trafficClassID = rx_info->traffic_class_id;
    rawRxMessage->rxInfo.remainHopLimit = rx_info->remain_hop_limit;
    rawRxMessage->rxInfo.security.status = rx_info->security.status;
    rawRxMessage->rxInfo.security.itsAID = rx_info->security.its_aid;
    rawRxMessage->rxInfo.security.sspLen = rx_info->security.ssp_len;
    OCTET_STRING_fromBuf(&rawRxMessage->rxInfo.security.ssp, reinterpret_cast<char *>(rx_info->security.ssp),
                         SSP_LENGTH);
    rawRxMessage->rxInfo.positionInfo.latitude = rx_info->position_info.latitude;
    rawRxMessage->rxInfo.positionInfo.longitude = rx_info->position_info.longitude;
    rawRxMessage->rxInfo.areaTypeInfo.type = rx_info->area_type_info.type;
    rawRxMessage->rxInfo.areaTypeInfo.distanceA = rx_info->area_type_info.distance_a;
    rawRxMessage->rxInfo.areaTypeInfo.distanceB = rx_info->area_type_info.distance_b;
    rawRxMessage->rxInfo.areaTypeInfo.angle = rx_info->area_type_info.angle;
    OCTET_STRING_fromBuf(&rawRxMessage->rxInfo.sourceMacAddress, reinterpret_cast<char *>(rx_info->source_mac_addr),
                         MAC_ADDR_SIZE);
}

// copied from Unex EU CAM example
void UnexITSG5InterfaceConnection::dumpRxInfo_(eu_caster_rx_info_t *rx_info) {
    logger_->WriteDebugEntry("dumpRxInfo_()");

    struct tm *timeinfo;
    char buffer[80];
    time_t t;

    t = rx_info->timestamp.tv_sec;
    timeinfo = localtime(&t);
    strftime(buffer, 80, "%Y%m%d%H%M%S", timeinfo);
    logger_->WriteDebugEntry("Timestamp: " + std::string(buffer));
    logger_->WriteDebugEntry("RSSI: " + std::to_string(rx_info->rssi));
    logger_->WriteDebugEntry("Data Rate: " + std::to_string(rx_info->data_rate));
    logger_->WriteDebugEntry("Remain Hop: " + std::to_string(rx_info->remain_hop_limit));
    logger_->WriteDebugEntry("Decap Status: " + std::to_string(rx_info->security.status));

    switch (rx_info->security.status) {
        case EU_SEC_DECAP_VERIFIED_PKT:
            logger_->WriteDebugEntry("Security Status: This packet is verified");
            logger_->WriteDebugEntry("ITS-AID: " + std::to_string(rx_info->security.its_aid));
            logger_->WriteDebugEntry("SSP Length: " + std::to_string(rx_info->security.ssp_len));

            for (uint8_t i = 0; i < rx_info->security.ssp_len; i++) {
                logger_->WriteDebugEntry("SSP[" + std::to_string(i) + "]: " + std::to_string(rx_info->security.ssp[i]));
            }
            break;

        case EU_SEC_DECAP_UNVERIFIABLE_PKT:
            logger_->WriteDebugEntry("Security Status: This packet is untrustworthy");
            break;

        case EU_SEC_DECAP_INVALID_FMT:
            logger_->WriteDebugEntry(
                    "Security Status: Decapsulation error (" + std::to_string(rx_info->security.status) +
                    "), the payload content is invalid");
            break;

        default:
            logger_->WriteDebugEntry("Security Status: Other (" + std::to_string(rx_info->security.status) + ")");
            break;
    }
    return;
}