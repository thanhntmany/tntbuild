#!/bin/bash
cd "$(dirname "$(readlink -f "$0")")"

bash ./build.sh

mkdir -p ./\$test/
dst=$(realpath ./\$test/test)
src=$(realpath ./test.c)
obj=$(realpath ./\$build/iofp.o)

pushd ../.. > /dev/null 2>&1
gcc -o $dst -I. $src $obj
popd > /dev/null 2>&1

cd ./\$test/
time $dst
