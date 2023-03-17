#!/bin/sh

mkdir -p build
cd build
conan install .. --build=missing
cmake ..
cmake --build . --target INSTALL
#doxygen doxygen.config