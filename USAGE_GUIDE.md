# Usage Guide

This Readme contains information on how to use the V2X Routing Platform.
Please make sure to understand the basics of V2X and the basics of the routing platform!

## Quickstart Guide
There are two possibilities to run the software

### Within a Docker
To start the routing platform, follow these steps.
- have some Linux OS with docker and git installed (tested with Ubuntu 20.04)
- check out this repo
- check out specific version (tagged)
- build and run the demo docker

```shell
./docker-demo-build-and-run.sh
```
- docker starts automatically
- attach to the logging output
```shell
docker logs -f v2x_routing-demo
```
- stop the docker when finished
```shell
docker stop v2x_routing-demo
```

### With the make file
The make file will run a docker build and output the files for you in the bin folders
```shell
echo "This will build the software locally
make local

echo "This will build the software, upload it to your docker repo and download it again.
make all
```

## Dev-Environments
You may develop either in the provided docker (recommended), or native

### Docker Dev-Environment (Recommended)
The Dev-Environment is provided as Docker.
CLion can be connected via Remote-SSH.
- have some Linux OS with docker, git and CLion installed (tested with Ubuntu 20.04 and CLion 2021.1.2)
- check out this repo
- check out specific version (tagged)
- build and run the dev docker
```shell
./docker-dev-build-and-run.sh
```
- docker starts automatically 
- connect CLion to the remote environment
  - user@password
  - port: 2222
- add Environment-Variables for CMake
  - CLion->settings->Build, Execution, Deployment->CMake->Environment Variables
  - ITSG5_SDK_PATH="ITSG5-Protocol-SDK-v1.7"
  - ARCH_FLAGS="-m32 -msse -msse2 -D__X86__"

#### Docker has to be restarted at system startup
```shell
docker start v2x_routing-dev
```

### Native Dev-Environment
You should definitely use the Docker setup, as the following instructions are already within the Dockerfile!

However, if you choose the manuel way, follow these steps:

- Install Linux 18.04 LTS 64-bit
- Minimum requirement for X86_32 target: GLIBC version 2.12 GLIBCXX version 3.4
- Minimum requirement for ARMv7a_32 target: GLIBC version 2.17 GLIBCXX version 3.4
- Installing GCC6
```shell
sudo apt-get update && \
sudo apt-get install build-essential software-properties-common -y && \
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y && \
sudo apt-get update && \
sudo apt-get install gcc-6 g++-6 -y && \
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6 && \
gcc -v
```
- Installing packages for compiling 32bit binary on 64bit Linux
```shell
sudo apt-get install lib32gcc-6-dev
sudo apt-get install libc6-dev-i386
```
- Installing Make and CMake
```shell
sudo apt-get install make
sudo apt-get install cmake
```
- Installing compiler for arm-linux-gnueabihf target
```shell
sudo apt-get install gcc-arm-linux-gnueabihf
sudo apt-get install g++-arm-linux-gnueabihf
sudo apt-get install linux-libc-dev:i386
```
- Install crosscompilation library
```shell
sudo apt-get install gcc-6-multilib g++-6-multilib
```
- get git and clone the code from the gitlab repo
```shell
sudo apt-get install git
git clone https://gitlab.v2c2.at/christophpilz/v2x-routing-platform.git
```
- export environment variables for cmake script
```shell
export ITSG5_SDK_PATH="ITSG5-Protocol-SDK-v1.7"
export ARCH_FLAGS="-m32 -msse -msse2 -D__X86__"
```
- build the code
```shell
cd v2x-routing-platform
mkdir build
cd build
cmake ..
make
./v2x-routing-platform
```
