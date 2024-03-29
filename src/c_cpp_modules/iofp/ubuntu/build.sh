#!/bin/bash

mkdir -p ./\$build/
name=iofp
dst=$(realpath ./\$build/$name.o)
src=$(realpath ../$name.c)

pushd ../.. > /dev/null 2>&1
gcc -Wall -o $dst -c $src
popd > /dev/null 2>&1