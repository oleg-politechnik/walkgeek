#!/bin/bash

cd gerber

[ -d info ] || mkdir info

for EXT in gpi dri
do
  LIST=*.$EXT
  [ -z LIST ] && continue
  for FROM in $LIST
  do
    mv $FROM "info/${FROM/%.$EXT/.txt}";
  done
done

