#!/bin/bash

. ./build.bi.sh

gcc -I../../ -o ./\$build/test test.c ./\$build/strbuf.o

echo test:
./\$build/test test.c