#!/bin/bash

tnt \
dst e3--test \
dep e3-test.c \
build-script "gcc -o \$(tnt @dst) \$(tnt @dep)"