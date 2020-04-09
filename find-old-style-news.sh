#!/bin/bash

find . -name "*.cpp" -exec grep -EHn "new [^{]*\(" {} \; | more
find . -name "*.cpp" -exec grep -EHn "Q[^{:\*]*\(" {} \; | grep -v QStringLiteral | grep -v QLatin1String | grep -v Q_EMIT | grep -v Q_DECL_OVERRIDE | more
