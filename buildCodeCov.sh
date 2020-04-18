#!/bin/sh

mkdir -p build && cd build

cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_COVERAGE=On ..
make gcov
make lcov
cd ..
