#!/bin/bash

#@main:main.c sub.c
cc -o main main.c sub.c
./main

#@sub.o: sub.c
cc -o sub.o -c sub.c
./main

#@main:main.c sub.c
cc -o mains main.c sub.o
./mains
