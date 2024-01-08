cmake_minimum_required(VERSION 3.10)

message(STATUS "--> Configure build of V2X Interface Control")

# set the project name
project("V2X Interface Control" VERSION 0.1 DESCRIPTION "V2X Interface Control for V2X Communication Platform")

# declare target as shared library
add_library(v2x_interface_control SHARED "")

# set target properties
set_target_properties(v2x_interface_control
        PROPERTIES
            COMPILE_FLAGS "-Wall -Wextra -fno-strict-aliasing -pipe $ENV{ARCH_FLAGS}"
            LINK_FLAGS "-Wall -Wextra -fno-strict-aliasing -pipe $ENV{ARCH_FLAGS}"
            VERSION ${PROJECT_VERSION}
)

## MQTT include stuff
# find the mqtt headers
find_path(PAHO_CPP_INCLUDE_DIR
        NAMES "mqtt"
        PATHS "/usr/include" "/usr/arm-linux-gnueabihf/include"
        )
# find the paho mqtt C lib
find_library(PAHO_MQTT3AS_LIB
        NAMES "paho-mqtt3as"
        PATHS "/usr/lib" "/usr/arm-linux-gnueabihf/lib"
        )
# find the paho mqtt C++ lib
find_library(PAHO_MQTTPP3_LIB
        NAMES "paho-mqttpp3"
        PATHS "/usr/lib" "/usr/arm-linux-gnueabihf/lib"
        )
message(STATUS "--> mqtt include path: " ${PAHO_CPP_INCLUDE_DIR})
message(STATUS "--> paho-mqtt3as path: " ${PAHO_MQTT3AS_LIB})
message(STATUS "--> paho-mqttpp3 path: " ${PAHO_MQTTPP3_LIB})

# specify header locations
target_include_directories(v2x_interface_control
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/include/v2x_interface_control
            ${CMAKE_HOME_DIRECTORY}/util/include
            ${CMAKE_HOME_DIRECTORY}/$ENV{ITSG5_SDK_PATH}/include
            ${CMAKE_HOME_DIRECTORY}/vcits
            ${CMAKE_HOME_DIRECTORY}/vcits/vcits/asn1c
            ${PAHO_CPP_INCLUDE_DIR}
)

# add the source files
target_sources(v2x_interface_control
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/src/V2XInterfaceConnection.cpp
            ${CMAKE_CURRENT_LIST_DIR}/src/MQTTInterfaceConnection.cpp
            ${CMAKE_CURRENT_LIST_DIR}/src/UnexITSG5InterfaceConnection.cpp
)

# link the target against the following libraries
target_link_libraries(v2x_interface_control
        PUBLIC
            itsg5_sdk
            utilityclasses
            vcits
            ${PAHO_MQTT3AS_LIB}
            ${PAHO_MQTTPP3_LIB}
)

message(STATUS "--> Configure build of V2X Interface Control - done")
