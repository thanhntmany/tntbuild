#!/bin/bash

. ./build.sh
mkdir -p ./\$test


obj=$dst
dst=$(realpath ./\$test/test)
src=$(realpath ./test.c)

pushd ../../ > /dev/null 2>&1
gcc -I. -o $dst $src $obj
popd > /dev/null 2>&1

time $dst
