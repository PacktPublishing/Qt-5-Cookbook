#!/bin/bash

MAX_LINES=$((`wc -l $1 | cut -d" " -f1 | wc -c` -1))

i=1
cat $1 | while IFS= read LINE; do
   printf "%0${MAX_LINES}d. %s\n" $i "$LINE"
   i=$((i+1))
done
