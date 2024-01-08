#!make
# 'make base' is needed to create basic images

ifneq (,$(wildcard ./.env))
    include .env
    export
endif

.PHONY: help
help: ## this help
	@printf "routing platform container build\n-------------------\n"
	@printf "explicit targets\n"
	@printf "you may want to execute 'make base' for the basic images"
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DEFAULT_GOAL := help

.PHONY: clean
clean: ## clean build files
	sudo $(RM) -r ${BUILD_DIR_ARMv8} ${BUILD_DIR_x64}

.PHONY: all
all: ## build docker images and compile executables
	./build_images.sh LOCAL_BUILD=0

.PHONY: base
base: ## build dependencies
	docker build -t build_paholib_x64:base -f Dockerfiles/Dockerfile_compile_paho_x64 .
	docker build -t build_paholib_armv8:base -f Dockerfiles/Dockerfile_compile_paho_armv8 .

.PHONY: local
local: ## build docker images and compile executables for local use (no image pushed)
	./build_images.sh LOCAL_BUILD=1

.PHONY: update
update: ## update base docker images (you should execute "make base" and "make all/local" afterwards to update all)
	docker pull arm64v8/ubuntu:18.04
	docker pull ubuntu:18.04

.PHONY: run
run: ## run routing platform docker image
	docker run -it --name v2x_routing-demo --rm ${DOCKER_RUN_IMAGE_NAME}:${DOCKER_RUN_IMAGE_TAG}
