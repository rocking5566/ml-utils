help:
	@cat Makefile

DATA?="${HOME}/Data"
DOCKER_FILE=Dockerfile
DOCKER=nvidia-docker
IMAGE_NAME=tensorflow
REPO_ROOT?=$(shell dirname `pwd`)/../../

X11_DISPLAY=--env DISPLAY=$(DISPLAY) \
	--env="QT_X11_NO_MITSHM=1" \
	-v /tmp/.X11-unix:/tmp/.X11-unix:ro

MOUNT_DIR=-v $(REPO_ROOT):/workspace \
	-v $(DATA):/datasets

MOUNT_WEBCAM=-v /dev/video0:/dev/video0

build:
	$(DOCKER) build -t $(IMAGE_NAME) -f $(DOCKER_FILE) .

bash:
	$(DOCKER) run -it --privileged --rm $(MOUNT_DIR) $(MOUNT_WEBCAM) --net=host $(IMAGE_NAME) bash

x11:
	xhost +
	$(DOCKER) run -it --privileged --rm $(MOUNT_DIR) $(X11_DISPLAY) $(MOUNT_WEBCAM) --net=host $(IMAGE_NAME) bash
	xhost -

ipython:
	$(DOCKER) run -it --rm $(MOUNT_DIR) $(IMAGE_NAME) ipython

notebook:
	$(DOCKER) run -it --rm $(MOUNT_DIR) --net=host $(IMAGE_NAME)

