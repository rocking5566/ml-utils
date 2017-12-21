help:
	@cat Makefile

DATA?="${HOME}/Data"
GPU?=0
DOCKER_FILE=Dockerfile
DOCKER=GPU=$(GPU) nvidia-docker
BACKEND=tensorflow
PYTHON_VERSION?=3.5
TEST=tests/
SRC?=$(shell dirname `pwd`)

X11_DISPLAY=--env DISPLAY=$(DISPLAY) \
	--env="QT_X11_NO_MITSHM=1" \
	-v /tmp/.X11-unix:/tmp/.X11-unix:ro

MOUNT_DIR=-v $(SRC):/src/workspace \
	-v $(DATA):/data

MOUNT_WEBCAM=-v /dev/video0:/dev/video0

build:
	docker build -t keras --build-arg python_version=$(PYTHON_VERSION) -f $(DOCKER_FILE) .

bash: build
	xhost +
	$(DOCKER) run -it --privileged --rm $(MOUNT_DIR) $(X11_DISPLAY) $(MOUNT_WEBCAM) --net=host --env KERAS_BACKEND=$(BACKEND) keras bash
	xhost -

ipython: build
	$(DOCKER) run -it --rm $(MOUNT_DIR) --env KERAS_BACKEND=$(BACKEND) keras ipython

notebook: build
	$(DOCKER) run -it --rm $(MOUNT_DIR) --net=host --env KERAS_BACKEND=$(BACKEND) keras

test: build
	$(DOCKER) run -it --rm $(MOUNT_DIR) --env KERAS_BACKEND=$(BACKEND) keras py.test $(TEST)


