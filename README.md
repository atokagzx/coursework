# Project on videobot
# Table of content
-  [General description](#general-description)
-  [Running manual](#manual)
## General description <a name="general-description"></a>

My coursework on the subject of "Programming Technologies". Telegram bot implements the receipt of short videos.

## Running manual <a name="manual"></a>

```bash
git clone https://github.com/atokagzx/coursework
cd coursework
touch config.txt
```
paste your token into `config.txt`
```bash
bash docker/buid_docker.sh
bash docker/run_docker.sh
```
you will be inside docker container, run following:
```bash
cd /videobot
mkdir build
cd build 
cmake ..
make
./src/videobot
```