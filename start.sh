#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Необходимо передать два имени файла."
    exit 1
fi

input_file="../$1"
output_file="../$2"

cd ./cmake_files
./TATLIN $input_file $output_file
cd ../
