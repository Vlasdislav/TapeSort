#!/bin/bash

cd ./cmake_files
make
mkdir files
./smoke_test
rm -r files
cd ../
