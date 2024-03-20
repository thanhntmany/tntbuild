#!/bin/bash

mkdir -p ./\$build/
name=sfile
dst=$(realpath ./\$build/$name.o)
src=$(realpath ../$name.c)

pushd ../.. > /dev/null 2>&1
gcc -o $dst -I. -c $src
popd > /dev/null 2>&1