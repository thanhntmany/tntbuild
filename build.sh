#!/bin/bash
SCRIPT_DIR=${BASH_SOURCE[0]}
cd "$SCRIPT_DIR"
file="tntbuild"
output_file=$(readlink -f "./build/${file}")

cc -o $output_file ./src/main.c