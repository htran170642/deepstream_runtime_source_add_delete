# RUNTIME SOURCE ADDITION DELETION REFERENCE APP USING DEEPSTREAMSDK 6.3

## Introduction
The project contains Runtime source addition/deletion application to show the
capability of Deepstream SDK.

## Reference:
[Deepstream reference app](https://github.com/NVIDIA-AI-IOT/deepstream_reference_apps/tree/master)

## Getting Started

- Preferably clone the app in
  `/opt/nvidia/deepstream/deepstream/sources/apps/sample_apps/`

- Edit all the inference models config files according to the location of the models to be used

## Compilation Steps and Execution:
```
  $ mkdir build && cd build && cmake ..
  $ make -j10

  $ ./build/deepstream-test-rt-src-add-del <uri> <run forever> <sink> <sync>
  $ ./build/deepstream-test-rt-src-add-del file:///opt/nvidia/deepstream/deepstream/samples/streams/sample_1080p_h265.mp4 0 nveglglessink 1 #dGPU - nveglglessink Jetson - nv3dsink
  $ ./build/deepstream-test-rt-src-add-del rtsp://localhost:5554/stream_1 0 nveglglessink 1 #dGPU
```

The application demonstrates following pipeline for single source <uri>

uridecodebin -> nvstreammux -> nvinfer -> nvtracker -> nvtiler -> nvvideoconvert -> nvdsosd -> displaysink

- At runtime after a timeout a source will be added periodically. All the components
  are reconfigured during addition/deletion
- After reaching of `MAX_NUM_SOURCES`, each source is deleted periodically till single
  source is present in the pipeline
- The app exits, when final source End of Stream is reached or if the last source is deleted.
- filesink and nv3dsink (only Jetson) are also supported.

## Blog:
https://developer.nvidia.com/blog/managing-video-streams-in-runtime-with-the-deepstream-sdk/


## Setup mysql with docker
https://ostechnix.com/setup-mysql-with-docker-in-linux/
bash
### Pull the mysql image
```
$ docker pull mysql:5.7
```

### Run the mysql container
```
$ docker run --name mysql -e MYSQL_ROOT_PASSWORD=admin -e MYSQL_DATABASE=mydb -e MYSQL_USER=test -e MYSQL_PASSWORD=123456 -p 3306:3306 -d mysql:5.7
```

### Connect to the mysql container
```
$ docker exec -it mysql bash
```

### Inside the container, connect to mysql using the root password
```
$ mysql -u root -p
```

### Create a new database
use script.sql example file

### issue when start mysql docker
```
$ sudo service mysql stop
```