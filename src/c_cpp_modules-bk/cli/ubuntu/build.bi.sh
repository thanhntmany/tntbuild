#!/bin/bash

target=$(realpath ./$build/cli)
pushd ../../ > /dev/null 2>&1
gcc -o "$target" -I. ./cli/cli.c app/app.c
popd > /dev/null 2>&1
