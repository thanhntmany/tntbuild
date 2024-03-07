#!/bin/bash

echo "
#@./tmp/main.o
#../src/main.c
#../src/app.c
cc -o $output_file main.c app.c
"
