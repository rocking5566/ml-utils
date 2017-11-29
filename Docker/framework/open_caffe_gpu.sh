echo "====================================================="
echo "Open container without saving state)"
echo "Usage: $0"
echo "====================================================="
echo "Open container with saving state"
echo "Usage: $0 [Container Name]"
echo "====================================================="
echo "It might take some time while executing this command in the first time"
echo "====================================================="

[ $# -eq 0 ] && nvidia-docker run -it --rm -v /:/workspace/host_os bvlc/caffe:gpu bash

if [ $# -eq 1 ]; then

    CONTAINER_NAME="$1"

    if [ ! "$(docker ps -aqf name=${CONTAINER_NAME})" ]; then
        nvidia-docker run -it --name ${CONTAINER_NAME} -v /:/workspace/host_os bvlc/caffe:gpu bash
    else
        nvidia-docker start -i ${CONTAINER_NAME}
    fi
fi
