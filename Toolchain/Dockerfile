FROM ubuntu:20.10

RUN DEBIAN_FRONTEND="noninteractive" apt-get update -y && apt-get install -y tzdata

RUN apt-get install -y build-essential cmake curl libmpfr-dev libmpc-dev libgmp-dev e2fsprogs qemu-utils wget genext2fs sudo ninja-build

RUN mkdir /serenity

WORKDIR /serenity

RUN /bin/bash

