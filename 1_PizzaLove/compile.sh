#!/bin/bash
clear
set -e
source filedata.txt
export env_filename=$filename
g++ -std=c++14 $filename.cpp -o $filename.out
#./$filename.out < sample.in
#./$filename.out < testInput > testOutput
./$filename.out < submitInput > submitOutput


# set -e
#   Any subsequent(*) commands failing makes the shell script to exit.

# source filedata.txt
#   Reads variables from filedata.txt

# mkdir -p
#   creates a folder only if it doesn't exist

# &> /dev/null
#   Suppreses output

# <	reads input from a file
# >	writes output to a file


#
# Author:      Eduardo Cáceres de la Calle
#
#
