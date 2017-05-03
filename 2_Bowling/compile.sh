#!/bin/bash
clear
set -e
source filedata.txt
export env_filename=$filename
g++ -std=c++14 $filename.cpp -o $filename.out
#./$filename.out < sample.in
#./$filename.out < testInput > testOutput
./$filename.out < submitInput > submitOutput


#
# Author:      Eduardo Cáceres de la Calle
#
#
