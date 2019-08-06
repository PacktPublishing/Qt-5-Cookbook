#!/bin/bash

cmake ..
bear make
#/usr/share/clang/run-clang-tidy.py -checks=*,-fuchsia-default-arguments ../src/*.cpp
find ../src/ -name "*.cpp" | xargs clazy-standalone -enable-all-fixits -checks=level2 -p compile_commands.json
find ../src/ -name "*.cpp" | xargs /usr/share/clang/run-clang-tidy.py -checks=*,-fuchsia-default-arguments
