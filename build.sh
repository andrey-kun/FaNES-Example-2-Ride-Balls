#!/bin/sh
PATH=".:$PATH" . project.cfg

rm build/ -R >> /dev/null 2>&1
mkdir build/

for cFile in `find . -type f -name "*.c"`
do
	asmFile=build/`basename -s .c $cFile`.s
	cc65 $cFile -Oir --static-locals -t nes -o "$asmFile" -I includes/ -g
	ca65 $asmFile -o build/`basename -s .c $cFile`.o
done

for asmFile in `find . -type f -name "*.s"`
do
	ca65 $asmFile -o build/`basename -s .s $asmFile`.o
done

ld65 -C cartboards/"$MAPPER"/"$MAPPER_CONF".cfg -o out/"$NAME_PROJECT".nes `find build/ -type f -name "*.o"` `echo $LIBRARIES_DEPEDENCY | sed 's/[^ ]*/libraries\/&.lib/g'`
