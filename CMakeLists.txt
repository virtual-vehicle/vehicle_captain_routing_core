cmake_minimum_required(VERSION 3.10)

# set the project name
project(V2X_Routing_Platform VERSION 0.2 DESCRIPTION "V2X Routing Platform" LANGUAGES C CXX)

# specify the C++ standard
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 14)

# set(CMAKE_C_COMPILER   /usr/bin/arm-linux-gnueabihf-gcc)
# set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)

# add targets
add_subdirectory($ENV{ITSG5_SDK_PATH})
add_subdirectory(util)
add_subdirectory(v2x_io_control)
add_subdirectory(v2x_interface_control)
add_subdirectory(v2x_routing)
add_subdirectory(vcits/vcits)

# add include directories
include_directories(.)
include_directories(util/include)
include_directories(v2x_io_control/include)
include_directories(v2x_interface_control/include)
include_directories(v2x_routing/include)
include_directories(vcits/vcits/asn1c) #vcits lib headers reference this

# add the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(v2xRoutingPlatform main.cpp)

# set target properties - CMake does not know without source files
set_target_properties(v2xRoutingPlatform
        PROPERTIES
            COMPILE_FLAGS "-Wall -Wextra -fno-strict-aliasing -pipe $ENV{ARCH_FLAGS} -leu_v2xcast -pthread -lrt -lm -lzmq"
            LINK_FLAGS "-Wall -Wextra -fno-strict-aliasing -pipe $ENV{ARCH_FLAGS} -leu_v2xcast -pthread -lrt -lm -lzmq"
            VERSION ${PROJECT_VERSION}
)

# link libraries
target_link_libraries(v2xRoutingPlatform
        PUBLIC
            utilityclasses
            v2x_io_control
            v2x_interface_control
            v2x_routing
            vcits
)

# add the binary tree to the search path for include files, to find them
#target_include_directories(V2X_Routing_Platform PUBLIC
#        "${PROJECT_BINARY_DIR}"
#        "${PROJECT_SOURCE_DIR}/$ENV{ITSG5_SDK_PATH}"
#        )
