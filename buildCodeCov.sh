#!/bin/sh

mkdir -p build && cd build

cmake -DCODE_COVERAGE:BOOL=TRUE ..
make -j$(nproc)
cd ..
