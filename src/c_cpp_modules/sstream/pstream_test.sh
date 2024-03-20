#!/bin/bash

clear
dst=./pstream
gcc -o $dst ./pstream.c
echo @==========================================
time $dst