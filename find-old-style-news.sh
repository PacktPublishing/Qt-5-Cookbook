#!/bin/bash

find . -name "*.cpp" -exec grep -EHn "new [^{]*\(" {} \; | more
