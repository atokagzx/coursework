ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"
docker run  -ti --rm \
               --privileged \
               -v $ROOT_DIR:/videobot \
               --name videobot videobot-img