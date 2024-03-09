#!/bin/bash
#TODO:
run_build_script () {
    echo Hello I am a function $1
}


target=$(realpath ./build/cli)
pushd ../../ > /dev/null 2>&1
gcc -o "$target" ./cli/cli.c
popd > /dev/null 2>&1

echo "========================"
$target -v ádá
echo "========================"
