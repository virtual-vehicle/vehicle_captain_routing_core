cmake_minimum_required(VERSION 3.10)

message(STATUS "--> Configure build of Utility Classes")

# set the project name
project("Utility Classes" VERSION 0.1 DESCRIPTION "Utility Classes for V2X Communication Platform")

# declare target as shared library
add_library(utilityclasses SHARED "")

# set target properties
set_target_properties(utilityclasses
        PROPERTIES
            LINKER_LANGUAGE CXX
            COMPILE_FLAGS "-Wall -Wextra -fno-strict-aliasing -pipe $ENV{ARCH_FLAGS}"
            LINK_FLAGS "-Wall -Wextra -fno-strict-aliasing -pipe $ENV{ARCH_FLAGS}"
            VERSION ${PROJECT_VERSION}
)

# specify header locations
target_include_directories(utilityclasses
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/include/util
            ${CMAKE_CURRENT_LIST_DIR}/include/util/encoder
            ${CMAKE_CURRENT_LIST_DIR}/include/util/exceptions
            ${CMAKE_CURRENT_LIST_DIR}/include/util/interfaces
            ${CMAKE_CURRENT_LIST_DIR}/include/util/logger
            ${CMAKE_CURRENT_LIST_DIR}/include/util/v2x_backend
)

# add the source files
target_sources(utilityclasses
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/src/encoder/base64.cpp
            ${CMAKE_CURRENT_LIST_DIR}/src/v2x_backend/V2XDefines.cpp
)

# link the target against the following libraries
#target_link_libraries(utilityclasses
#        PUBLIC
#            itsg5_sdk
#)

message(STATUS "--> Configure build of Utility Classes - done")