#!/bin/bash
cd "$(dirname "$(readlink -f "$0")")"

mkdir -p ./\$build/
name=sbuf
dst=$(realpath ./\$build/$name.o)
src=$(realpath ../$name.c)

cd ../..

gcc -Wall -o $dst -I. -c $src
gcc -Wall -o $dst.s -I. -S $src