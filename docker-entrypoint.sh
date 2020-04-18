#!/bin/sh

[ $1 == "Debug" ] && ./build.sh
[ $1 == "Release" ] && ./buildRelease.sh
[ $1 == "Debug" ] && cd build
[ $1 == "Release" ] && cd buildRelease 

make -j$(nproc) package
make -j$(nproc) install
cd ..

[ $1 == "Debug" ] && chmod -R 777 build bin
[ $1 == "Release" ] && chmod -R 777 buildRelease bin 
