#!/bin/bash

# Generates a lib directory containing all libraries
# required to run the Qt application (including platform
# plugin's dependencies)

if [ $# -ne 2 ];
   then echo "Usage: collect-cpp-dependencies.sh <qt-installation-path> <path-to-executable>"
   exit -1
fi

# Copy Qt modules libraries
rm -rf lib
mkdir lib
ldd -r $2 | egrep -o '/.*/lib.*\.so.*' | cut -d" " -f1 | while read LIBRARY; do cp -L $LIBRARY lib/; done
ldd -r $1/plugins/platforms/libqxcb.so | egrep -o '/.*/lib.*\.so.*' | cut -d" " -f1 | while read LIBRARY; do cp -L $LIBRARY lib/; done

# Copy platform plugin
mkdir platforms
cp $1/plugins/platforms/libqxcb.so platforms/

cp `dirname "$0"`/application-launcher.sh $2.sh
