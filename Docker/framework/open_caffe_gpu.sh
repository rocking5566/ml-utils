echo "====================================================="
echo "Open container without saving state)"
echo "Usage: $0"
echo "====================================================="
echo "Open container with saving state"
echo "Usage: $0 [Container Name]"
echo "====================================================="
echo "It might take some time while executing this command in the first time"
echo "====================================================="

xhost +
[ $# -eq 0 ] && GPU=0 nvidia-docker run  --privileged -it --rm \
                      --env DISPLAY=$DISPLAY \
                      --env="QT_X11_NO_MITSHM=1" \
                      -v /dev/video0:/dev/video0 \
                      -v /tmp/.X11-unix:/tmp/.X11-unix:ro  \
                      -v /:/workspace/host_os bvlc/caffe:gpu bash

if [ $# -eq 1 ]; then

    CONTAINER_NAME="$1"

    if [ ! "$(docker ps -aqf name=${CONTAINER_NAME})" ]; then
        GPU=0 nvidia-docker run --privileged -it --name ${CONTAINER_NAME} \
              --env DISPLAY=$DISPLAY \
              --env="QT_X11_NO_MITSHM=1" \
              -v /dev/video0:/dev/video0 \
              -v /tmp/.X11-unix:/tmp/.X11-unix:ro  \
              -v /:/workspace/host_os bvlc/caffe:gpu bash
    else
        GPU=0 nvidia-docker start -i ${CONTAINER_NAME}
    fi
fi
xhost -
