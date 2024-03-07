#!/bin/bash


SCRIPT_DIR=$(pwd)
SRC_DIR=$SCRIPT_DIR/src
DST_DIR=$SCRIPT_DIR/dst

output_file=$DST_DIR/tnt

pushd $SRC_DIR > /dev/null 2>&1
cc -o $output_file main.c app.c
popd > /dev/null 2>&1
