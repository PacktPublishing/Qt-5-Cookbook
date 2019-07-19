#!/bin/bash

# Generates a lib directory containing all libraries
# required to run the Qt application (including platform
# plugin's dependencies)

if [ $# -ne 1 ];
   then echo "Usage: collect-dependencies.sh <path-to-executable>"
   exit -1
fi

rm -rf lib
mkdir lib
ldd -r $1 | egrep -o '/usr/lib/lib.*\.so' | while read LIBRARY; do cp -a $LIBRARY* lib/; done
ldd -r /usr/lib/qt/plugins/platforms/libqxcb.so | egrep -o '/usr/lib/lib.*\.so' | while read LIBRARY; do cp -a $LIBRARY* lib/; done
