#################################################################################
# Copyright (c) 2020-2021, NVIDIA CORPORATION.  All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

CUDA_VER?=
ifeq ($(CUDA_VER),)
  $(error "CUDA_VER is not set")
endif

APP:= deepstream-test-rt-src-add-del

TARGET_DEVICE = $(shell g++ -dumpmachine | cut -f1 -d -)

DS_SDK_ROOT:=/opt/nvidia/deepstream/deepstream

LIB_INSTALL_DIR?=$(DS_SDK_ROOT)/lib/

SRCS:= $(wildcard *.cpp)

INCS:= $(wildcard *.h)

PKGS:= gstreamer-1.0

OBJS:= $(SRCS:.cpp=.o)

CFLAGS+= -I$(DS_SDK_ROOT)/sources/includes \
 -I /usr/local/cuda-$(CUDA_VER)/include 
#  -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
#  -I/usr/include/mysql 

CFLAGS+= `pkg-config --cflags $(PKGS)`

LIBS:= `pkg-config --libs $(PKGS)`

LIBS+= -L$(LIB_INSTALL_DIR) -lnvdsgst_helper -lm -lnvdsgst_meta \
 -L/usr/local/cuda-$(CUDA_VER)/lib64/ -lcudart -lmysqlcppconn -lglib-2.0  \
 -lcuda -Wl,-rpath,$(LIB_INSTALL_DIR)

all: $(APP)

.o: .c $(INCS) Makefile
	$(CC) -c $@ $(CFLAGS) $<

$(APP): $(OBJS) Makefile
	$(CC) -o $(APP) $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS) $(APP)


