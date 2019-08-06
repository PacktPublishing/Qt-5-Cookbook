#!/bin/bash

cmake ..
bear make
find ../src/ -name "*.cpp" | xargs clazy-standalone -enable-all-fixits -checks=level0,level1,level2,level3,assert-with-side-effects,container-inside-loop,heap-allocated-small-trivial-type,ifndef-define-typo,inefficient-qlist,isempty-vs-count,qhash-with-char-pointer-key,qrequiredresult-candidates,qstring-varargs,qt-keywords,qt4-qstring-from-array,qvariant-template-instantiation,raw-environment-function,reserve-candidates,signal-with-return-value,thread-with-slots,tr-non-literal,unneeded-cast -p compile_commands.json
find ../src/ -name "*.cpp" | xargs /usr/share/clang/run-clang-tidy.py -checks=*,-fuchsia-default-arguments
