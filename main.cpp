//
// Created by christophpilz on 19.04.2021.
//
// reference: https://bytefreaks.net/programming-2/c/asn1c-full-working-example-of-asn-1-in-cc
//

/// TODO list
/// [] store GNSS separately
/// [] send GNSS via UDP
/// [] send CAM with plausible content
/// [] send CAM with GPS from variable -> for high precision GNSS
/// []
/// [] better handling for signal loop
/// [] have some standard for console logging
/// [] check potential for another class for static unex methods
/// [] refactor C-Style defines

#include <chrono>
#include <iostream>
#include <thread>
#include <tuple>
//#include <optional> //C++17
#include <experimental/optional>

#include <csignal>
/*
extern "C" {
#include "itsg5_sdk/itsg5_caster_service.h"
#include "itsg5_sdk/error_code_user.h"
#include "itsg5_sdk/poti_caster_service.h"

#include "vcits/cam/CAM.h"
#include "vcits/denm/DENM.h"
#include "vcits/parser/Decoder.h"
}
*/
#include "util/logger/LoggingFacility.h"
#include "util/logger/StandardOutputLogger.h"
#include "util/logger/ClassStandardOutputLogger.h"
/*
#include "util/ThreadsafeQueue.h"

#include "v2x_interface_control/V2XInterfaceConnection.h"
#include "v2x_interface_control/UnexITSG5InterfaceConnection.h"
*/

#include "v2x_io_control/CommunicationControl.h"
#include "v2x_routing/V2XRoutingControl.h"
#include "v2x_routing/zmq/LightWeightZmqRoutingControl.h"
#include "v2x_routing/zmq/BaseZmqRoutingControl.h"

sig_atomic_t stopFlag = 0;

void signalHandler(int) {
    stopFlag = 1;
}

int main() {
    Logger *logger = new ClassStandardOutputLogger(Logger::LogLevel::ALL, "main");
    logger->WriteInfoEntry("Unex Wrapper Test");

    signal(SIGINT, &signalHandler);
    signal(SIGTERM, &signalHandler);

    int ret = 0;
    std::experimental::optional<std::tuple<void *, size_t>> v2x_msg;

    int rc_hz = 10; //10Hz
    int cc_hz = 10; //10Hz

    V2XRoutingControl *rc = new LightWeightZmqRoutingControl("raw.", "v2x.", 1000/rc_hz, "LW-RoutingControl", Logger::LogLevel::INFO);
    CommunicationControl *cc = new CommunicationControl(1000/cc_hz,"CommControl", Logger::LogLevel::INFO);

    rc->Configure();
    cc->Configure();

    rc->StartUp();
    cc->StartUp();

    std::thread *rc_thread = new std::thread([&]() {
        rc->run();
    });
    std::thread *cc_thread = new std::thread([&]() {
        cc->run();
    });

    while(!stopFlag){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    logger->WriteInfoEntry("Going to stop");

    cc->stop();
    cc_thread->join();
    rc->stop();
    rc_thread->join();

    logger->WriteInfoEntry("Going to shutdown");
    cc->ShutDown();
    rc->ShutDown();

    cc->Cleanup();
    rc->Cleanup();

    delete cc_thread;
    delete rc_thread;

    delete cc;
    delete rc;

    /*
    CAM_t *current_cam = nullptr;
    DENM_t *current_denm = nullptr;
    V2XInterfaceConnection *v2x_ic = new UnexITSG5InterfaceConnection("192.168.1.3", 0, Logger::LogLevel::DEBUG);

//    UDPHandler udp_handler("172.20.2.4");
//    udp_handler.initializeClient();
//    udp_handler.initializeServer();

//    udp_handler.send(current_cam_v2);
//    udp_handler.receive(received_cam_v2);



    ret = v2x_ic->Connect();
    if (ret == 0) {
        v2x_ic->run();

        while (!stopFlag) {
//            udp_handler.receive(received_cam_v2);
//            if (uw.getCamV2FromQueue(current_cam_v2) == 0) {
//                udp_handler.send(current_cam_v2);
//            }

            v2x_msg = v2x_ic->Receive();
            if (v2x_msg)
                current_cam = (CAM_t *) Decoder::decode(&asn_DEF_CAM, std::get<0>(v2x_msg.value()), std::get<1>(v2x_msg.value()));
            if (v2x_msg)
                current_denm = (DENM_t *) Decoder::decode(&asn_DEF_DENM, std::get<0>(v2x_msg.value()), std::get<1>(v2x_msg.value()));

            if (current_cam != nullptr) {
                std::cout << "Header.protocolVersion: " << current_cam->header.protocolVersion << std::endl;
                std::cout << "Header.messageID: " << current_cam->header.messageID << std::endl;
                std::cout << "Header.stationID: " << current_cam->header.stationID << std::endl;

                std::cout << "cam.generationDeltaTime: " << current_cam->cam.generationDeltaTime << std::endl;
                std::cout << "cam.camParameters.basicContainer.stationType: "
                          << current_cam->cam.camParameters.basicContainer.stationType << std::endl;
                std::cout << "cam.camParameters.basicContainer.referencePosition.latitude: "
                          << current_cam->cam.camParameters.basicContainer.referencePosition.latitude << std::endl;
                std::cout << "cam.camParameters.basicContainer.referencePosition.longitude: "
                          << current_cam->cam.camParameters.basicContainer.referencePosition.longitude << std::endl;
                std::cout << "cam.camParameters.basicContainer.referencePosition.altitude.altitudeValue: "
                          << current_cam->cam.camParameters.basicContainer.referencePosition.altitude.altitudeValue
                          << std::endl;

//                udp_handler.send(std::get<0>(v2x_msg), std::get<1>(v2x_msg));

                ASN_STRUCT_FREE(asn_DEF_CAM, current_cam);
                current_cam = nullptr;
            }

            if (current_denm != nullptr) {
                std::cout << "Header.protocolVersion: " << current_denm->header.protocolVersion << std::endl;
                std::cout << "Header.messageID: " << current_denm->header.messageID << std::endl;
                std::cout << "Header.stationID: " << current_denm->header.stationID << std::endl;

                ASN_STRUCT_FREE(asn_DEF_DENM, current_denm);
                current_denm = nullptr;
            }

            if(v2x_msg)
                for(int i = 0; i < 3; i++){
                    logger->WriteDebugEntry("Prepare sending");
                    void* v2x_send = malloc(std::get<1>(v2x_msg.value()));
                    // no sanity check
                    memcpy(v2x_send, std::get<0>(v2x_msg.value()), std::get<1>(v2x_msg.value()));

                    std::tuple<void *, size_t> v2x_msg_send;
                    v2x_msg_send = std::make_tuple(v2x_send, std::get<1>(v2x_msg.value()));

                    v2x_ic->Send(v2x_msg_send);
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }

            if(v2x_msg)
                free(std::get<0>(v2x_msg.value()));

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    logger->WriteInfoEntry("Going to stop");

    v2x_ic->stop();
    v2x_ic->Close();

//    udp_handler.closeClient();
//    udp_handler.closeServer();
*/
    logger->WriteInfoEntry("Done");

    return ret;
}
