#!/bin/sh

./build.sh
cd build
make package
make install
cd ..
chmod -R 777 build bin
