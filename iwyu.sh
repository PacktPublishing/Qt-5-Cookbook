#!/bin/bash

cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
iwyu-tool -v -p . -- -Xiwyu --mapping=../../../qt5_4.imp | sed -n '/should remove these lines:/,/^$/p'
