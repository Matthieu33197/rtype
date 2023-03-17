#!/bin/sh

mkdir -p build
cd build
conan install .. --build=missing -c tools.system.package_manager:mode=install
cmake ..
make
make install
cd ..
#doxygen doxygen.config