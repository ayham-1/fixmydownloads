#!/bin/sh

[ $1 == "Debug" ] && ./build.sh
[ $1 == "Release" ] && ./buildRelease.sh
cd build
make -j5 package
make -j5 install
cd ..
chmod -R 777 build bin
