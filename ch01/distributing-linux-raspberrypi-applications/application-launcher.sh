#!/bin/sh
appname=`basename $0 | sed s,\.sh$,,`

dirname=`dirname $0`
tmp="${dirname#?}"

if [ "${dirname%$tmp}" != "/" ]; then
   dirname=$PWD/$dirname
fi
export LD_LIBRARY_PATH=$dirname/lib
export QML2_IMPORT_PATH=$dirname/qml
$dirname/$appname "$@"
