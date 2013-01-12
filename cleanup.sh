#!/bin/sh
make clean &> /dev/null
find . -name "CMakeFiles" -exec rm -rf '{}' \; &> /dev/null 
find . -name "cmake_install.cmake" -delete 
find . -name "CMakeCache.txt" -delete
find . -name "Makefile" -delete
rm -rf ../build