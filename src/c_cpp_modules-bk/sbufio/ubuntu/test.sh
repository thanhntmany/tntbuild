#!/bin/bash
cd "$(dirname "$(readlink -f "$0")")"

bash ./build.sh
obj=$(realpath ./\$build/sbufio.o)


mkdir -p ./\$test/
dst=$(realpath ./\$test/test)
src=$(realpath ./test.c)

pushd ../.. > /dev/null 2>&1
bash ./sbuf/ubuntu/build.sh
bash ./iofp/ubuntu/build.sh
bash ./memp/ubuntu/build.sh

gcc -o $dst -I. $src \
    $obj \
    ./sbuf/ubuntu/\$build/sbuf.o \
    ./iofp/ubuntu/\$build/iofp.o \
    ./memp/ubuntu/\$build/memp.o

popd > /dev/null 2>&1

cd ./\$test/
time $dst
