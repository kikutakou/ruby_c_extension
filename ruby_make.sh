#!/bin/bash


[ -d "$1" ] || { echo "usage : $(basename $0) [dir]" ; exit 1 ;}


cd "$1"

#get library name from .c .cc .cpp
INIT_LIB=$(find . -name "*.cpp" -o -name "*.c" -o -name "*.cc" | xargs -L 1 grep -oE "Init_[a-zA-Z]+")
[ -n "$INIT_LIB" ] || { echo "Error : Init_{LIBRARY_NAME} function not found in dir $1" ; exit 1 ;}
LIB_NAME="${INIT_LIB#Init_}"

set -e

#create_makefile
echo " @ create makefile"
ruby -r "mkmf" -e "create_makefile(\"${LIB_NAME}\")"

#make
echo " @ make"
make

#remove object file and Makefile
rm -rf *.o Makefile


#test
[ -e "test.rb" ] || exit
echo " @ test"
ruby "test.rb"
