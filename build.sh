#!/bin/sh

objs=" "

for i in $(find src/ -type f -name '*.c')
do
	echo "Compiling $i"
	gcc -o ${i/.*}.o -c $i -O2 -Wall -Wextra -Werror
done

gcc -o xenit $(find src/ -type f -name '*.o') -static -O2
