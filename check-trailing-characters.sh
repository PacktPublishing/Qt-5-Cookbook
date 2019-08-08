#!/bin/bash

find . -name "*.qml" -exec grep -Hn  "[[:blank:]]$" {} \; | grep -v build
find . -name "*.h" -exec grep -Hn  "[[:blank:]]$" {} \; | grep -v build
find . -name "*.cpp" -exec grep -Hn  "[[:blank:]]$" {} \; | grep -v build

# Run: kate `./check-trailing-characters.sh` &
# Search, with regular expressions, for: ^\s+$
# Remove all trailing characters/blank lines
