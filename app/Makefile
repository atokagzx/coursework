SHELL=/bin/bash
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR=/opt/videobot/build

all: build install generate_docs

build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake $(ROOT_DIR) && make -j$(nproc)

install:
	cd $(BUILD_DIR) && make install

generate_docs:
	doxygen $(ROOT_DIR)/Doxyfile 