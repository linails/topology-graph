#! /bin/sh
# Created Time: 2016-10-10 16:44:00
#

./swig-py.sh

python setup.py build

cp build/lib.linux-x86_64-2.7/* ../python/
echo "cp build/lib.linux-x86_64-2.7/* ../python/"
