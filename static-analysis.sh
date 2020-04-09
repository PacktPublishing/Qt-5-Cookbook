#!/bin/bash

cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
find ../src/ -name "*.cpp" | xargs clazy-standalone -checks=level0,level1,level2,assert-with-side-effects,container-inside-loop,inefficient-qlist,isempty-vs-count,qhash-with-char-pointer-key,qrequiredresult-candidates,qstring-varargs,qt-keywords,qt4-qstring-from-array,qvariant-template-instantiation,raw-environment-function,reserve-candidates,thread-with-slots,tr-non-literal,unneeded-cast -p compile_commands.json
find ../src/ -name "*.cpp" | xargs /usr/share/clang/run-clang-tidy.py -checks=*,-fuchsia-default-arguments,-fuchsia-default-arguments-declarations,-cppcoreguidelines-owning-memory,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-readability-implicit-bool-conversion,-llvm-header-guard,-cppcoreguidelines-macro-usage,-cppcoreguidelines-special-member-functions,-modernize-use-trailing-return-type,-hicpp-special-member-functions,-fuchsia-default-arguments-calls -header-filter=../src/
