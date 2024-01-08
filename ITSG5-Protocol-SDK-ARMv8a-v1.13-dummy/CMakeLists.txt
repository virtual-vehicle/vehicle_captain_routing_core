cmake_minimum_required(VERSION 3.10)

message(STATUS "--> Configure build of ITSG5-Protocol-SDK-ARMv8a-V1.13")

# set the project name
project("Unex ITSG5 SDK" VERSION 1.13 DESCRIPTION "Shared Library for the Unex ITS-G5 SDK")

# declare target as shared library
add_library(itsg5_sdk SHARED "")

# set target properties - CMake does not know without source files
set_target_properties(itsg5_sdk
        PROPERTIES
        LINKER_LANGUAGE C
        COMPILE_FLAGS "-std=gnu99 -Wall -Wextra -fno-strict-aliasing -pipe $ENV{ARCH_FLAGS} -leu_v2xcast -pthread -lrt -lm -lzmq"
        LINK_FLAGS "-std=gnu99 -Wall -Wextra -fno-strict-aliasing -pipe $ENV{ARCH_FLAGS} -leu_v2xcast -pthread -lrt -lm -lzmq"
)

# add sources
#add_subdirectory(src)

# specify header locations
target_include_directories(itsg5_sdk
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/itsg5_sdk
)

# find libraries
find_library(ITSG5_V2XCAST
        NAMES
        "eu_v2xcast"
        HINTS
        ${CMAKE_CURRENT_LIST_DIR}/lib
)
find_library(ITSG5_ZMQ
        NAMES
        "zmq"
        HINTS
        ${CMAKE_CURRENT_LIST_DIR}/lib
)

message(STATUS "--> v2xcast path: " ${ITSG5_V2XCAST})
message(STATUS "--> zmq path: " ${ITSG5_ZMQ})

# link the target against the following libraries
target_link_libraries(itsg5_sdk
        PUBLIC
        ${ITSG5_V2XCAST}
        ${ITSG5_ZMQ}
)

message(STATUS "--> Configure build of ITSG5-Protocol-SDK-ARMv8a-V1.13 - done")