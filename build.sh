#!/bin/sh

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j5
cd ..
