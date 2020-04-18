#!/bin/bash
dir=`pwd`
mkdir -p build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$dir ..
make install
