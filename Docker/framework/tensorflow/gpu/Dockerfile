FROM gcr.io/tensorflow/tensorflow:1.5.0-devel-gpu-py3

RUN apt-get update && \
    apt-get install -y cmake \
    libgl1-mesa-glx \
    libhdf5-dev \
    g++ \
    graphviz \
    openmpi-bin \
    vim \
    libgtk2.0-dev \
    pkg-config \
    libcanberra-gtk-module \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev

# OpenCV
# [Warning] - opencv-python does not include Video I/O (Can not open Webcam)
# Build opencv from source

ARG opencv_version=3.3.0

ENV OPENCV_DIR /opt/opencv

RUN mkdir -p $OPENCV_DIR 

WORKDIR $OPENCV_DIR

RUN wget https://github.com/Itseez/opencv/archive/${opencv_version}.zip -O opencv-${opencv_version}.zip

RUN unzip opencv-${opencv_version}.zip && \
    cd opencv-${opencv_version} &&\
    mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=$(python -c "import sys; print(sys.prefix)") \
    -D WITH_TBB=ON \
    -D WITH_V4L=ON \
    -D WITH_CUDA=OFF \
    -D WITH_EIGEN=OFF \
    -D WITH_OPENCL=OFF \
    -D BUILD_opencv_python3=YES \
  ..

RUN cd opencv-${opencv_version}/build && \
    make -j4 && \
    make install && \
    rm $OPENCV_DIR/opencv-${opencv_version}.zip

WORKDIR /

RUN pip install --upgrade --ignore-installed setuptools && pip install --no-cache-dir git+git://github.com/ppwwyyxx/tensorpack
RUN pip install beautifulsoup4 lxml cython

# [Warning] - Do not use root in public IP 

CMD jupyter notebook --allow-root --port=8888 --ip=0.0.0.0 & \
    tensorboard --logdir=/log/tensorboard