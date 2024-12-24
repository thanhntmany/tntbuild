#!/bin/bash

mkdir -p ./\$build
dst=$(realpath ./\$build/app.o)

pushd .. > /dev/null 2>&1
echo gcc -c $dst ./app.c
popd > /dev/null 2>&1