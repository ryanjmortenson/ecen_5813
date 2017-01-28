#/usr/bin/env bash

find . -name "*.py" -o -name "*.c" -o -name "*.h" -o -name "*.cpp" > files.txt
cscope -i files.txt -b
rm files.txt
