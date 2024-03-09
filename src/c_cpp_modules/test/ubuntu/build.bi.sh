#!/bin/bash

src_dir=..
dst=./build/test
gcc -o $dst $src_dir/test.c
$dst