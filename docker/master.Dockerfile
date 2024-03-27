FROM ubuntu:22.04

LABEL Yaroslav Savelev "y.savelev@edu.misis.ru"

# Timezone Configuration
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && apt install -y apt-utils \
                                lsb-release \
                                mesa-utils \
                                gnupg2 \
                                net-tools \
                                build-essential \
                                wget \
                                unzip \
                                curl \
                                libcurl4-openssl-dev \
                                git \
                                g++ \
                                make \
                                binutils \
                                cmake \
                                libssl-dev \
                                libboost-system-dev \
                                zlib1g-dev \
    && apt clean && rm -rf /var/lib/apt/lists/*

RUN apt update && apt install -y doxygen doxygen-doc graphviz \
    && apt clean && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src
# very important libraries :)
RUN git clone https://github.com/reo7sp/tgbot-cpp.git -b v1.7.3 \
    && cd tgbot-cpp \
    && cmake . \
    && make -j4 \
    && make install

RUN apt update && apt install -y libpq-dev libpqxx-dev \
    && apt clean && rm -rf /var/lib/apt/lists/*