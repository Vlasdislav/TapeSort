#!/bin/bash

rm -r cmake_files
mkdir cmake_files
cd cmake_files
cmake ../
make
cd ../
