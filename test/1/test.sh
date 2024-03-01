#!/bin/bash
pushd "../../" > /dev/null 2>&1

source "build.sh"
$out_put_file

popd > /dev/null 2>&1
