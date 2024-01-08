# Docker Build Infrastructure
For the docker make toolchain to work, please setup docker as follows:

## Docker Setup
Please follow this guide for the docker setup

### Install Docker via script
```bash
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
sudo groupadd -f docker
sudo usermod -aG docker pi
reboot
```

### Check if Docker is working
```bash
docker run --rm hello-world
```

### Configure Docker to be compatible with ViF internal network
```bash
sudo nano /etc/docker/daemon.json
```
```bash
{
        "default-address-pools":[
                {"base":"172.17.0.0/16","size":24},
                {"base":"172.18.0.0/16","size":24},
                {"base":"172.19.0.0/16","size":24},
                {"base":"172.23.0.0/16","size":24}
        ]
}
```

## Multi Architecture Build
Please install additional tools for crosscompilation

### Install arm64 support
```bash
sudo apt update
sudo apt install binfmt-support
sudo apt install qemu-user-static
```

### Enable experimental features of docker
```bash
nano $HOME/.docker/config.json
```
```bash
# add:
{
  # ...
  "experimental": "enabled"
}
```
Pro tip: this should be valid JSON .. there must be a comma "," at the end of the line above "experimental".


### Create bootstrap builder
```bash
docker buildx create --name mbuilder
docker buildx use mbuilder
docker buildx inspect --bootstrap
```

### Check if used base-image supports arm64/v8
```bash
docker buildx imagetools inspect python:3.8-slim
# --> look for arm64/v8
```

### Finally: make sure you are logged in into your chosen docker repo!
```bash
docker login
```