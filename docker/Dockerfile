ARG from

FROM ${from}

LABEL Yaroslav Savelev "m2003578@edu.misis.ru"

# Timezone Configuration
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get install -y apt-utils \
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
                                         mc \
                                         vim \
                                         g++ \
                                         make \
                                         binutils \
                                         cmake \
                                         libssl-dev \
                                         libboost-system-dev \
                                         zlib1g-dev

# very important libraries :)
RUN git clone https://github.com/reo7sp/tgbot-cpp.git \
    && cd tgbot-cpp \
    && cmake . \
    && make -j4 \
    && make install