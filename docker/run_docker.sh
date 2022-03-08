ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"
docker run  -ti --rm \
               --privileged \
               -v $ROOT_DIR:/videobot \
               -v $ROOT_DIR/token.txt:/BOT_DB/token.txt \
               -v $ROOT_DIR/database:/BOT_DB/database \
               --name videobot videobot-img