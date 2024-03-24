#!/bin/bash

. ./build.sh
obj=$dst

mkdir -p ./\$test/

dst=$(realpath ./\$test/test)
src=$(realpath ./test.c)

pushd ../.. > /dev/null 2>&1

# pushd ./pstream/ubuntu > /dev/null 2>&1
# . ./build.sh
# obj="$obj $dst"
# popd > /dev/null 2>&1

gcc -o $dst -I. $src $obj ./pstream/ubuntu/\$build/pstream.o

popd > /dev/null 2>&1

pushd ./\$test/ > /dev/null 2>&1
time $dst
popd > /dev/null 2>&1
