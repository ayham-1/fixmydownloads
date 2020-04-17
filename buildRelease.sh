#!/bin/bash

mkdir buildRelease
cd buildRelease
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j5
cd ..
