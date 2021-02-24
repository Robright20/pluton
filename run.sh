#!/bin/bash
SRC=./champs/*.s

for f in $SRC
do
	echo "----------------------------------------------------------------------------"
	echo "$f"
	./asm $f
	./test $f
done
rm -f ./champs/*.cor
