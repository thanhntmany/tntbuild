#!/bin/bash
cd "$(dirname "$(readlink -f "$0")")"

bash ./build.sh

mkdir -p ./\$test/
dst=$(realpath ./\$test/test)
src=$(realpath ./test.c)
obj=$(realpath ./\$build/iofpb.o)


pushd ../.. > /dev/null 2>&1
bash ./iofp/ubuntu/build.sh
gcc -o $dst -I. $src $obj ./iofp/ubuntu/\$build/iofp.o
popd > /dev/null 2>&1

cd ./\$test/
time $dst
