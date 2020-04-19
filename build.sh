#!/bin/bash
dir=$(dirname $(readlink -f "$0"))
mkdir -p build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$dir ..
make install
