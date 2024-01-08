#!/bin/bash

# this script is executed in compilation docker

# stop on error
set -e

# build x64 binary
echo "build x64 binary"
export ARCH_FLAGS=""
# export ITSG5_SDK_PATH="ITSG5-Protocol-SDK-v1.7"
export ITSG5_SDK_PATH=$(find /tmp/compile -maxdepth 1 -type d -name "${ITSG5_SDK_DIR_PATTERN_x64}" | sed "s|^/tmp/compile/||")
echo "ITSG5_SDK_PATH: ${ITSG5_SDK_PATH}"
# build_x64 directory needs to be mapped as volume to docker container
cd /tmp/compile/${BUILD_DIR_x64}
cmake ..
make -j$(nproc)
echo "build x64 binary - done"

# build armv8 binary
echo "build armv8 binary"
export ARCH_FLAGS=""
# export ITSG5_SDK_PATH="ITSG5-Protocol-SDK-ARMv8-v1.13"
export ITSG5_SDK_PATH=$(find /tmp/compile -maxdepth 1 -type d -name "${ITSG5_SDK_DIR_PATTERN_ARMv8}" | sed "s|^/tmp/compile/||")
echo "ITSG5_SDK_PATH: ${ITSG5_SDK_PATH}"
# build_armv8 directory needs to be mapped as volume to docker container
cd /tmp/compile/${BUILD_DIR_ARMv8}
cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc-8" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++-8" \
      -D CMAKE_PREFIX_PATH="/usr/aarch64-linux-gnu" ..
make -j$(nproc)
echo "build armv8 binary - done"
