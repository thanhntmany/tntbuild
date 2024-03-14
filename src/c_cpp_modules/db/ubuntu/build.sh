#!/bin/bash

mkdir -p ./\$build
dst=$(realpath ./\$build/test)

pushd .. > /dev/null 2>&1
gcc ./test.c -o $dst
popd > /dev/null 2>&1

chmod +X $dst

time $dst