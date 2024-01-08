# Usage Guide

This Readme contains information on how to use the V2X Routing Platform.
Please make sure to understand the basics of V2X and the basics of the routing platform!

## Three Build&Run Options
There are three possibilities to run the software
- running it locally (release)
- using the dev docker (development)
- compiling natively (if you like pain)

### Running the software locally
The software will be compiled by the make script. The resulting x64 and ARM binaries can be run on respective host machines.

- configure local user to be in docker group
```
sudo groupadd -f docker
usermod -aG docker $USER
sudo reboot
```
- compile the base images
```
make base
```
- compile the source
```
make local
```
- create IPC folders
```
mkdir -p /tmp/v2x/in && mkdir -p /tmp/v2x/out && chmod 777 /tmp/v2x/in && chmod 777 /tmp/v2x/out
```
- copy lib files to /usr/lib
```
sudo mv ./build_x64/libs_x64/* /usr/lib/
sudo mv ./build_armv8/libs_armv8/* /usr/lib/
```
- start executable
```
build_x64/bin/v2xRoutingPlatform
build_armv8/bin/v2xRoutingPlatform
```

### Create Docker Dev-Environment (Recommended for Development)
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
  - ITSG5_SDK_PATH="ITSG5-Protocol-SDK-v1.13"
  - ARCH_FLAGS=""

#### Docker has to be restarted at system startup
```shell
docker start v2x_routing-dev
```

### Configurations in CLion
- the docker has to be running, otherwise the connection is going to be refused
- make the following configurations either for sender or receiver

  ##### Toolchain Configuration
  - File -> Settings -> Build, Execution, Deployment -> Toolchains
  - Click "+" and "New Remote Host"
  - Configure new remote (SSH Configurations):
    - Host: localhost
    - Port: 2222
    - Username: user
    - Password: password

  ##### CMake Configuration
  - File -> Settings -> Build, Execution, Deployment -> CMake
  - Click "+" and name it "Debug-Remote" for example
  - Select the previously created toolchain
  - Reload the CMake Project (open CMake file in CLion and click Reload CMake project)

### Native Dev-Environment
You should definitely use the Docker setup, as the following instructions are already within the Dockerfile!

However, if you choose the manual way, follow these steps:

- Install Linux 18.04 LTS 64-bit
- Minimum requirement for X86_32 target: GLIBC version 2.12 GLIBCXX version 3.4
- Minimum requirement for ARMv7a_32 target: GLIBC version 2.17 GLIBCXX version 3.4
- Installing GCC8
```shell
sudo apt-get update && \
sudo apt-get install build-essential software-properties-common -y && \
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y && \
sudo apt-get update && \
sudo apt-get install gcc-8 gcc-8-multilib g++-8 g++-8-multilib -y && \
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 80 --slave /usr/bin/g++ g++ /usr/bin/g++-8 && \
gcc -v
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
- Installing compiler for gcc-8-aarch64-linux-gnu target
```shell
sudo apt-get install -y gcc-8-aarch64-linux-gnu
sudo apt-get install -y g++-8-aarch64-linux-gnu
```
- get git and clone the code from the gitlab repo
```shell
sudo apt-get install git
git clone https://gitlab.v2c2.at/christophpilz/v2x-routing-platform.git
```
- export environment variables for cmake script
```shell
export ITSG5_SDK_PATH="ITSG5-Protocol-SDK-v1.13"
export ARCH_FLAGS=""
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
