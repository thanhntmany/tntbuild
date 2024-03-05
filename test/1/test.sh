#!/bin/bash
pushd "../../" > /dev/null 2>&1
. "./build.sh"
popd > /dev/null 2>&1

time $output_file -d "12354645" -bbss load ./b.bi.sh