#!/bin/bash

# Usage:
# ./generate-gif.sh <output.gif>

while [ "$(magick identify "$(ls -1 *.png | head -n 1)" | sed -n 's/.*PNG \([0-9]*\)x\([0-9]*\).*/\1/p')" -gt 128 ]; do
   mogrify -path . -resize 50% *.png
done

mkdir crop
convert -composite *.png composite.png
ls -1 *.png | while read IMG; do
   convert -composite $IMG composite.png composite.png
done

OUTPUT=$(convert composite.png -verbose -trim composite.png)
NEWSIZE=$(echo $OUTPUT | sed -n 's/.*=>\([0-9]*x[0-9]*\).*/\1/p')
OFFSET=$(echo $OUTPUT | sed -n 's/.*\(+[0-9]*+[0-9]*\).*/\1/p')
rm -rf composite.png

mogrify -path ./crop -background transparent -crop "$NEWSIZE$OFFSET" +repage *.png

OUTPUT=$1
shift
if [ ! -z "$@" ]; then
   magick mogrify -path ./crop "$@" crop/*.png
fi

convert -set dispose background -loop 0 -delay 3 ./crop/*.png $OUTPUT

rm -r crop
