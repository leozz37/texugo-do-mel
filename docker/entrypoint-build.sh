#!/bin/sh

git clone git@github.com:leozz37/core-messaging.git
cd core-messaging
git checkout develop
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/opt/mongo-cxx-driver/3.4.0 ..
make -j4
mkdir -p /root/artifacts
cp ../core-messaging /root/artifacts
cd ../../
cd /root/artifacts && ls -la