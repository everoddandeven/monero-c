#!/bin/sh

#EMCC_DEBUG=1

HOST_NCORES=$(nproc 2>/dev/null || shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

# build libmonero-cpp shared library
cd ./external/monero-cpp/ && 
./bin/build_libmonero_cpp.sh &&
cd ../../ &&

# build libmonero-c shared library to ./build
mkdir -p build &&
cd build && 
cmake .. && 
cmake --build . -j$HOST_NCORES && 
make .
