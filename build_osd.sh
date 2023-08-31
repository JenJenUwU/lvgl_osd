#!/bin/bash

rm -rf build/
cmake -Bbuild -DCMAKE_TOOLCHAIN_FILE=../cmake/sigmastar.cmake -DSDK_DIR=/home/sigmastar/release_1122/sourcecode -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
#cmake -Bbuild -DSDK_DIR=/home/sigmastar/release_1122/sourcecode -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
cmake --build build
