#!/bin/sh

mkdir -p build && cd build

cmake -DENABLE_COVERAGE:BOOL=TRUE ..
make -j$(nproc)
cd ..
