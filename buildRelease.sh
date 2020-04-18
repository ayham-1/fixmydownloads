#!/bin/bash

mkdir -p buildRelease
cd buildRelease
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
cd ..
