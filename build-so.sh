#! /bin/sh
# Created Time: 2016-10-11 14:57:47
#

if [ "`which pip`" ]; then
    echo ""
    echo "python-pip installed"
    echo ""
    if [ "`which swig`" ]; then
        echo ""
    else
        echo ""
        echo "installing python-libs"
        sudo apt-get update
        ./docs/install-python-lib.sh
        echo ""
    fi
else
    echo ""
    echo "installing python-libs"
    sudo apt-get update
    ./docs/install-python-lib.sh
    echo ""
fi

cd clib

./swig-py.sh

echo ""
echo "###########################################"
echo ""
python setup.py build

cp build/lib.linux-x86_64-2.7/* ../python/

echo "###########################################"
echo ""
echo "cp clib/build/lib.linux-x86_64-2.7/*.so /python/"
echo ""
echo "###########################################"
echo ""

