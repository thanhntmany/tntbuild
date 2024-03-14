#!/bin/bash

mkdir -p ./\$build
dst=$(realpath ./\$build/strbuf.o)

pushd .. > /dev/null 2>&1
gcc -c ./strbuf.c -o $dst
popd > /dev/null 2>&1