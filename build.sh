#!/bin/bash
SCRIPT_DIR=${BASH_SOURCE[0]}
cd "$SCRIPT_DIR"
file="tntbuild"
out_put_file=./build/$file

cc -o $out_put_file ./src/$file.c