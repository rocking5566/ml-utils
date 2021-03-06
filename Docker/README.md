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
```

## Create environment in Docker
### Keras
To run the clean Keras (GPU) environment
```sh
$ cd Docker/framework/keras/gpu
$ sudo make build   # Build docker file
$ sudo make bash
```
Run the clean Keras (GPU) environment on the web (IPython notebook and TensorBoard)
```sh
$ cd Docker/framework/keras/gpu
$ sudo make notebook
```
You will see the notebook and Tensorboard URL in the terminal

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