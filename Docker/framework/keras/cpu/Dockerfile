FROM ubuntu

ENV CONDA_DIR /opt/conda
ENV PATH $CONDA_DIR/bin:$PATH

RUN mkdir -p $CONDA_DIR && \
    echo export PATH=$CONDA_DIR/bin:'$PATH' > /etc/profile.d/conda.sh && \
    apt-get update && \
    apt-get install -y unzip cmake wget git \
    libhdf5-dev g++ graphviz openmpi-bin vim \
    libgtk2.0-dev pkg-config \
    libcanberra-gtk-module \
    libavcodec-dev libavformat-dev libswscale-dev && \
    wget --quiet https://repo.continuum.io/miniconda/Miniconda3-4.2.12-Linux-x86_64.sh && \
    echo "c59b3dd3cad550ac7596e0d599b91e75d88826db132e4146030ef471bb434e9a *Miniconda3-4.2.12-Linux-x86_64.sh" | sha256sum -c - && \
    /bin/bash /Miniconda3-4.2.12-Linux-x86_64.sh -f -b -p $CONDA_DIR && \
    rm Miniconda3-4.2.12-Linux-x86_64.sh

RUN mkdir -p $CONDA_DIR && \
    mkdir -p /src

# Python
ARG python_version=3.5

RUN conda install -y python=${python_version} && \
    pip install --upgrade pip && \
    pip install tensorflow && \
    pip install https://cntk.ai/PythonWheel/CPU-Only/cntk-2.3-cp35-cp35m-linux_x86_64.whl && \
    conda install Pillow scikit-learn notebook pandas matplotlib mkl nose pyyaml six h5py && \
    conda install theano bcolz && \
    pip install sklearn_pandas && \
    git clone git://github.com/keras-team/keras.git /src && pip install -e /src[tests] && \
    pip install git+git://github.com/keras-team/keras.git && \
    pip install pydot && \
    pip install graphviz && \
    pip install html5lib==0.999999999 && \
    conda clean -yt

ADD theanorc /home/keras/.theanorc

ENV PYTHONPATH='/src/:$PYTHONPATH'

WORKDIR /src

# OpenCV
# [Warning] - opencv-python does not include Video I/O (Can not open Webcam)
# Build opencv from source

ARG opencv_version=3.2.0

ENV OPENCV_DIR /src/opencv

RUN mkdir -p $OPENCV_DIR && cd $OPENCV_DIR && \
    wget https://github.com/Itseez/opencv/archive/${opencv_version}.zip -O opencv-${opencv_version}.zip

RUN cd $OPENCV_DIR && \
    unzip opencv-${opencv_version}.zip && \
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
    -D PYTHON3_EXECUTABLE=$(which python3) \
    -D PYTHON3_LIBRARIES=/opt/conda/lib/libpython${python_version}m.so  \
    -D PYTHON_INCLUDE_DIR=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())") \
    -D PYTHON3_PACKAGES_PATH=$(python -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())") \
    -D PYTHON3_NUMPY_INCLUDE_DIRS=/opt/conda/lib/python${python_version}/site-packages/numpy/core/include \
  ..

RUN cd $OPENCV_DIR/opencv-${opencv_version}/build && \
    make -j4 && \
    make install

RUN rm $OPENCV_DIR/opencv-${opencv_version}.zip && apt-get -y install libgl1-mesa-glx

EXPOSE 8888 6006

# [Warning] - Do not use root in public IP 

CMD jupyter notebook --allow-root --port=8888 --ip=0.0.0.0 & \
    tensorboard --logdir=/src/tensorboard
    