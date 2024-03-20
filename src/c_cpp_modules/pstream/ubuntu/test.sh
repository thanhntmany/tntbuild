#!/bin/bash

. ./build.sh
obj=$dst

mkdir -p ./\$test/

dst=$(realpath ./\$test/test)
src=$(realpath ./test.c)

pushd ../.. > /dev/null 2>&1
gcc -o $dst -I. $src $obj
popd > /dev/null 2>&1

pushd ./\$test/ > /dev/null 2>&1
$dst
popd > /dev/null 2>&1
