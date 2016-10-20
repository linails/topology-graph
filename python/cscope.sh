#! /bin/sh
# Created Time: 2016-09-26 00:00:24
#

find . -name "*.h" -name "*.hpp" -o -name "*.c" -o -name "*.cpp" -o -name "*.cc" \
    -o -name "*.py" > cscope.files

cscope -bkq -i cscope.files

ctags -R

