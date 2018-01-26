help:
	@cat Makefile

DATA?="${HOME}/Data"
GPU?=0
DOCKER_FILE=Dockerfile
DOCKER=GPU=$(GPU) nvidia-docker
BACKEND=tensorflow
TEST=tests/
SRC?=$(shell dirname `pwd`)

X11_DISPLAY=--env DISPLAY=$(DISPLAY) \
	--env="QT_X11_NO_MITSHM=1" \
	-v /tmp/.X11-unix:/tmp/.X11-unix:ro

MOUNT_DIR=-v $(SRC):/src/pwd \
	-v $(DATA):/data  \
	-v /home/rocking/data/keras:/root/.keras/datasets \
	-v /home/rocking/data/keras:/tmp/.keras/datasets \
	-v /home/rocking/work/ml-util/Example/keras:/src/hostOs \
	-v /home/rocking/data:/src/dataset \
	-v /media/rocking/5402723902722062/work:/src/win_work \
	-v /home/rocking/work:/src/work

MOUNT_WEBCAM=-v /dev/video0:/dev/video0

build:
	docker build -t tf_objdet --build-arg python_version=$(PYTHON_VERSION) -f $(DOCKER_FILE) .

bash: build
	xhost +
	$(DOCKER) run -it --privileged --rm $(MOUNT_DIR) $(X11_DISPLAY) $(MOUNT_WEBCAM) --net=host --env KERAS_BACKEND=$(BACKEND) tf_objdet bash
	xhost -

ipython: build
	$(DOCKER) run -it --rm $(MOUNT_DIR) --env KERAS_BACKEND=$(BACKEND) tf_objdet ipython

notebook: build
	$(DOCKER) run -it --rm $(MOUNT_DIR) --net=host --env KERAS_BACKEND=$(BACKEND) tf_objdet

test: build
	$(DOCKER) run -it --rm $(MOUNT_DIR) --env KERAS_BACKEND=$(BACKEND) tf_objdet py.test $(TEST)


