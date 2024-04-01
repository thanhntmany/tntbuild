#!/bin/bash
cd "$(dirname "$(readlink -f "$0")")"

mkdir -p ./\$build/
name=iofpi
dst=$(realpath ./\$build/$name.o)
src=$(realpath ../$name.c)

cd ../..
bash ./iofp/ubuntu/build.sh

gcc -Wall -I. -o $dst -c $src
# gcc -Wall -o $dst.s -S $src
