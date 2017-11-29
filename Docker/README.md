# Docker Environment

- Install Docker CE
- Install Nvidia Docker
- Run Docker Container

## Installation
### Ubuntu 16.04

For developer environments
```sh
$ sudo ./install_docker_ce_ubuntu_amd64.sh
$ sudo ./install_nvidia_docker_ubuntu_amd64.sh

# [Option] Test is Docker CE installed correctly
$ docker run --rm hello-world

# [Option] Test nvidia-smi with the latest official CUDA image
# This command will take a long time
$ docker run --runtime=nvidia --rm nvidia/cuda nvidia-smi
```

For production environments
- To do

### Redhat 7.0
- To do

## Create environment in Docker
### Caffe
To run the clean caffe environment

```sh
$ sudo ./framework/open_caffe_gpu.sh
```

However, this command will not save the environment.
If you want to save the environment, just give environment a name
```sh
$ sudo ./framework/open_caffe_gpu.sh "test"
```
To Test is caffe environment correct.
Let's train LeNet on MNIST
```sh
$ cd $CAFFE_ROOT
$ ./data/mnist/get_mnist.sh
$ ./examples/mnist/create_mnist.sh
$ ./examples/mnist/train_lenet.sh
```

If you see "Optimization Done" in the console like following. Congratulation!

```sh
I1129 03:51:48.452687    39 caffe.cpp:259] Optimization Done.
```