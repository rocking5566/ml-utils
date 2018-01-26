FROM keras

RUN apt-get install -y protobuf-compiler python-pil python-lxml
RUN git clone https://github.com/tensorflow/models.git /src/tf_model
RUN cd /src/tf_model/research && protoc object_detection/protos/*.proto --python_out=.

# PYTHONPATH=$PYTHONPATH::/src/tf_model/research/slim/
ENV PYTHONPATH='$PYTHONPATH:/src/tf_model/research:/src/tf_model/research/slim'

