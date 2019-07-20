#!/bin/bash

# Generates a lib directory containing all libraries
# required to run the Qt application (including platform
# plugin's dependencies)

if [ $# -ne 2 ];
   then echo "Usage: collect-qml-dependencies.sh <qt-installation-path> <path-to-qml-sources>"
   exit -1
fi

QT_INSTALLATION_PATH=$1
rm -rf /tmp/FOUND

function collect-qml()
{
   echo $FOUNDQMLDIR | sed s,\/qmldir$,, >> /tmp/FOUND
   fgrep depends $1 | cut -d" " -f2 | while read MODULE; do
      find $QT_INSTALLATION_PATH/qml/ -name qmldir | while read QMLDIR; do
         egrep -E -H "module $MODULE$" $QMLDIR | cut -d":" -f1 | while read FOUNDQMLDIR; do
            collect-qml $FOUNDQMLDIR
         done
      done
   done
}

fgrep import `find $2 -name *.qml` | cut -d" " -f2 | while read MODULE; do
   find $QT_INSTALLATION_PATH/qml/ -name qmldir | while read QMLDIR; do
      egrep -E -H "module $MODULE$" $QMLDIR | cut -d":" -f1 | while read FOUNDQMLDIR; do
         collect-qml $FOUNDQMLDIR
      done
   done
done

cat /tmp/FOUND | sort -u | while read MODULE; do
   BASEDIR=`echo $MODULE | sed s,[^/]*$,, | sed s,^$QT_INSTALLATION_PATH/,,`
   mkdir -p $BASEDIR
   cp -r $MODULE $BASEDIR
done

find ./qml -name *.so | while read LIB; do
   ldd -r $LIB | egrep -o '/.*/lib.*\.so.*' | cut -d" " -f1 | while read LIBRARY; do cp -L $LIBRARY lib/; done
done

rm -rf /tmp/FOUND
