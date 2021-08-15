#!/bin/sh

for file in $(find src/ -type f -name '*.c')
do
	gcc -o $file.o -c $file -static -O2
done

gcc -o xenit $(find src/ -type f -name '*.o')
