cmake_minimum_required(VERSION 3.10)

message(STATUS "--> Configure build of V2X IO Control")

# set the project name
project("V2X IO Control" VERSION 0.1 DESCRIPTION "V2X IO Control for V2X Communication Platform")

# declare target as shared library
add_library(v2x_io_control SHARED "")

# set target properties
set_target_properties(v2x_io_control
        PROPERTIES
            COMPILE_FLAGS "-Wall -Wextra -fno-strict-aliasing -pipe $ENV{ARCH_FLAGS}"
            LINK_FLAGS "-Wall -Wextra -fno-strict-aliasing -pipe $ENV{ARCH_FLAGS}"
            VERSION ${PROJECT_VERSION}
)

### load in pkg-config support
#find_package(PkgConfig)
### use pkg-config to get hints for 0mq locations
#pkg_check_modules(PC_ZeroMQ QUIET zmq)
#
### use the hint from above to find where 'zmq.hpp' is located
#find_path(ZeroMQ_INCLUDE_DIR
#        NAMES zmq
#        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
#        )
#
### use the hint from above to find the location of libzmq
#find_library(ZeroMQ_LIBRARY
#        NAMES zmq
#        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
#        )
#message(${PC_ZeroMQ_INCLUDE_DIRS} ... ${PC_ZeroMQ_LIBRARY_DIRS})

find_library(ITSG5_ZMQ
        NAMES
        "zmq"
        HINTS
        ${CMAKE_HOME_DIRECTORY}/$ENV{ITSG5_SDK_PATH}/lib
        )
message(AUTHOR_WARNING "V2X Routing uses Unex ZMQ lib: ${ITSG5_ZMQ}")

# specify header locations
target_include_directories(v2x_io_control
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/include/v2x_io_control
            ${CMAKE_CURRENT_LIST_DIR}/include/v2x_io_control/input_handling_strategies
            ${CMAKE_CURRENT_LIST_DIR}/include/v2x_io_control/output_handling_strategies
            ${CMAKE_HOME_DIRECTORY}/lib/libzmq/include
            ${CMAKE_HOME_DIRECTORY}/lib/cppzmq
            ${CMAKE_HOME_DIRECTORY}/util/include
            ${CMAKE_HOME_DIRECTORY}/v2x_interface_control/include
)

# add the source files
target_sources(v2x_io_control
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/src/CommunicationControl.cpp
            ${CMAKE_CURRENT_LIST_DIR}/src/InputHandlingStrategy.cpp
            ${CMAKE_CURRENT_LIST_DIR}/src/OutputHandlingStrategy.cpp
            ${CMAKE_CURRENT_LIST_DIR}/src/input_handling_strategies/ZmqSimpleInputHandlingStrategy.cpp
            ${CMAKE_CURRENT_LIST_DIR}/src/output_handling_strategies/ZmqSimpleOutputHandlingStrategy.cpp
)

# link the target against the following libraries
target_link_libraries(v2x_io_control
        PUBLIC
            utilityclasses
            v2x_interface_control
            ${ITSG5_ZMQ}
)

message(STATUS "--> Configure build of V2X IO Control - done")
