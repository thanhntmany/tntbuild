#!/bin/bash
cd "$(dirname "$(readlink -f "$0")")"

mkdir -p ./\$build/
name=memp
dst=$(realpath ./\$build/$name.o)
src=$(realpath ../$name.c)

cd ../..

gcc -Wall -o $dst -c $src
gcc -Wall -o $dst.s -S $src