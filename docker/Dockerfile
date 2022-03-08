ARG from

FROM ${from}

LABEL Yaroslav Savelev "y.savelev@edu.misis.ru"

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

RUN git clone https://github.com/doxygen/doxygen.git 

RUN apt install flex -y \
    && apt install bison -y \
    && cd doxygen \
    && cmake -G "Unix Makefiles" . \
    && make \
    && make install
    
RUN apt install graphviz -y
RUN mkdir /BOT_DB