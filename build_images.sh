#!/bin/bash

# stop on error
set -e

# EXPECTED ARGUMENTS:
# LOCAL_BUILD=0/1

# parse arguments
for ARGUMENT in "$@"
do
   KEY=$(echo $ARGUMENT | cut -f1 -d=)

   KEY_LENGTH=${#KEY}
   VALUE="${ARGUMENT:$KEY_LENGTH+1}"

   export "$KEY"="$VALUE"
done

if [ -z "$LOCAL_BUILD" ]; then
  echo "ERROR: local/pushed build not set (LOCAL_BUILD)"
  exit 1
elif [ "$LOCAL_BUILD" == "0" ]; then
  echo "LOCAL_BUILD=$LOCAL_BUILD"
else
  LOCAL_BUILD="1"
  echo "LOCAL_BUILD=$LOCAL_BUILD"
fi

SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
cd $SCRIPT_DIR

source .env

# build compilation image
echo "building ${DOCKER_BUILD_IMAGE_NAME}:${DOCKER_BUILD_IMAGE_TAG}"
DOCKER_BUILDKIT=0 docker build \
    -t ${DOCKER_BUILD_IMAGE_NAME}:${DOCKER_BUILD_IMAGE_TAG} \
    -f Dockerfiles/Dockerfile_compile \
    .
echo "building ${DOCKER_BUILD_IMAGE_NAME}:${DOCKER_BUILD_IMAGE_TAG} - done"

# prepare build-output folders
mkdir -p ${BUILD_DIR_x64} ${BUILD_DIR_ARMv8}

# prepare docker-parameter for mounting source folders as volumes

# find top-level folders containing files with .c .cpp .h .hpp .so extensions
readarray -t SOURCE_VOLUMES < <(find ./* \
    -path ./${BUILD_DIR_x64} -prune -o \
    -path ./${BUILD_DIR_ARMv8} -prune -o \
    -type f \
    -regex '.*\.\(c\|cpp\|h\|hpp\|so\)$' \
    -printf "%H\n" |sort -u)

for i in ${!SOURCE_VOLUMES[@]}; do
    # remove './' in paths
    SOURCE_VOLUMES[i]="${SOURCE_VOLUMES[i]/'./'/''}"
    # add leading '-v absolute_path'
    # add trailing ':/tmp/compile/THEPATH'
    SOURCE_VOLUMES[i]="-v ${SCRIPT_DIR}/${SOURCE_VOLUMES[i]}:/tmp/compile/${SOURCE_VOLUMES[i]}"
done

# for i in ${!SOURCE_VOLUMES[@]}; do
#     echo ${SOURCE_VOLUMES[i]}
# done
# echo ${SOURCE_VOLUMES[@]}

# compile! (make sure all used directories are mapped)
docker run -it --rm \
    ${SOURCE_VOLUMES[@]} \
    -v $(pwd)/CMakeLists.txt:/tmp/compile/CMakeLists.txt \
    -v $(pwd)/main.cpp:/tmp/compile/main.cpp \
    -v $(pwd)/${BUILD_DIR_x64}:/tmp/compile/${BUILD_DIR_x64} \
    -v $(pwd)/${BUILD_DIR_ARMv8}:/tmp/compile/${BUILD_DIR_ARMv8} \
    -e BUILD_DIR_x64="${BUILD_DIR_x64}" \
    -e BUILD_DIR_ARMv8="${BUILD_DIR_ARMv8}" \
    -e ITSG5_SDK_DIR_PATTERN_x64="${ITSG5_SDK_DIR_PATTERN_x64}" \
    -e ITSG5_SDK_DIR_PATTERN_ARMv8="${ITSG5_SDK_DIR_PATTERN_ARMv8}" \
    ${DOCKER_BUILD_IMAGE_NAME}:${DOCKER_BUILD_IMAGE_TAG}

# collect compiled libs
LIBS_x64_DEST=./${BUILD_DIR_x64}/libs_x64
mkdir -p ${LIBS_x64_DEST}
rm -rf ${LIBS_x64_DEST}/* || true
find ./${BUILD_DIR_x64} -path ${LIBS_x64_DEST} -prune -o -name "*.so*" -exec cp '{}' ${LIBS_x64_DEST}/ ';'
find ./${ITSG5_SDK_DIR_PATTERN_x64} -path ${BUILD_DIR_x64} -prune -o -name "*.so*" -exec cp '{}' ${LIBS_x64_DEST}/ ';'
CONT_ID=$(docker create --name tempcontainer build_paholib_x64:base)
docker cp $CONT_ID:/paho.mqtt.c_install/lib/. ${LIBS_x64_DEST}
docker cp $CONT_ID:/paho.mqtt.cpp_install/lib/. ${LIBS_x64_DEST}
docker rm tempcontainer


LIBS_ARMV8_DEST=./${BUILD_DIR_ARMv8}/libs_armv8
mkdir -p ${LIBS_ARMV8_DEST}
rm -rf ${LIBS_ARMV8_DEST}/* || true
find ./${BUILD_DIR_ARMv8} -path ${LIBS_ARMV8_DEST} -prune -o -name "*.so*" -exec cp '{}' ${LIBS_ARMV8_DEST}/ ';'
find ./${ITSG5_SDK_DIR_PATTERN_ARMv8} -path ${BUILD_DIR_ARMv8} -prune -o -name "*.so*" -exec cp '{}' ${LIBS_ARMV8_DEST}/ ';'
CONT_ID=$(docker create --name tempcontainer build_paholib_armv8:base)
docker cp $CONT_ID:/paho.mqtt.c_install/lib/. ${LIBS_ARMV8_DEST}
docker cp $CONT_ID:/paho.mqtt.cpp_install/lib/. ${LIBS_ARMV8_DEST}
docker rm tempcontainer

echo ""
if [ "$LOCAL_BUILD" == "0" ]; then

  echo "building image for cross-platform"
  # build cross-platform image for execution on PC or raspi
  docker buildx build --progress=plain --platform ${RUN_PLATFORMS} \
      -t ${DOCKER_RUN_IMAGE_NAME}:${DOCKER_RUN_IMAGE_TAG} \
      -f Dockerfiles/Dockerfile_run \
      --build-arg BUILD_DIR_x64="${BUILD_DIR_x64}" \
      --build-arg BUILD_DIR_ARMv8="${BUILD_DIR_ARMv8}" \
      --build-arg LIBS_x64_DEST="${LIBS_x64_DEST}" \
      --build-arg LIBS_ARMV8_DEST="${LIBS_ARMV8_DEST}" \
      --cache-from=type=registry,ref=${DOCKER_RUN_IMAGE_NAME}:cache \
      --cache-to=type=registry,ref=${DOCKER_RUN_IMAGE_NAME}:cache,mode=max \
      --push \
      .

      # --cache-from=type=registry,ref=${DOCKER_RUN_IMAGE_NAME}:cache \
      # --cache-to=type=registry,ref=${DOCKER_RUN_IMAGE_NAME}:cache,mode=max \
      # --no-cache \

  # make built image available on local machine
  docker pull ${DOCKER_RUN_IMAGE_NAME}:${DOCKER_RUN_IMAGE_TAG}

else

  echo "building image locally: $DOCKER_RUN_IMAGE_NAME:$DOCKER_RUN_IMAGE_TAG"
  docker build \
      -t ${DOCKER_RUN_IMAGE_NAME}:${DOCKER_RUN_IMAGE_TAG} \
      -f Dockerfiles/Dockerfile_run \
      --build-arg BUILD_DIR_x64="${BUILD_DIR_x64}" \
      --build-arg BUILD_DIR_ARMv8="${BUILD_DIR_ARMv8}" \
      --build-arg LIBS_x64_DEST="${LIBS_x64_DEST}" \
      --build-arg LIBS_ARMV8_DEST="${LIBS_ARMV8_DEST}" \
      --build-arg TARGETPLATFORM="linux/amd64" \
      .

fi

