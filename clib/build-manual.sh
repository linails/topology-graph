#! /bin/sh
# Created Time: 2016-10-20 16:53:00
#

c_compiler="x86_64-unknown-linux-gnu-gcc-4.9.2"
cxx_compiler="x86_64-unknown-linux-gnu-g++"

ccpara="-std=c99 -pthread -fno-strict-aliasing -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -fPIC -I/usr/include/python2.7"
cxxcpara="-std=c++11 -pthread -fno-strict-aliasing -DNDEBUG -g -fwrapv -O2 -Wall -fPIC -I/usr/include/python2.7"

objdir="build/temp.linux-x86_64-2.7"

mkdir build/lib.linux-x86_64-2.7

mkdir build/temp.linux-x86_64-2.7
mkdir build/temp.linux-x86_64-2.7/src
mkdir build/temp.linux-x86_64-2.7/src/graph
mkdir build/temp.linux-x86_64-2.7/src/test
mkdir build/temp.linux-x86_64-2.7/src/io

$c_compiler $ccpara -c czigbee_wrap.c -o $objdir/czigbee_wrap.o
$c_compiler $ccpara -c ./src/czigbee.c -o $objdir/./src/czigbee.o
$c_compiler $ccpara -c ./src/graph/calc_points.c -o $objdir/./src/graph/calc_points.o
$c_compiler $ccpara -c ./src/test/test.c -o $objdir/./src/test/test.o

$cxx_compiler $cxxcpara -c ./src/graph/cube.cpp -o $objdir/./src/graph/cube.o
$cxx_compiler $cxxcpara -c ./src/graph/sphere.cpp -o $objdir/./src/graph/sphere.o
$cxx_compiler $cxxcpara -c ./src/graph/route-tree.cpp -o $objdir/./src/graph/route-tree.o
$cxx_compiler $cxxcpara -c ./src/io/serial.cpp -o $objdir/./src/io/serial.o

$cxx_compiler -std=c++11 \
              -pthread \
              -shared \
              -Wl,-O1 \
              -Wl,-Bsymbolic-functions \
              -Wl,-Bsymbolic-functions \
              -Wl,-z,relro \
              -fno-strict-aliasing \
              -DNDEBUG \
              -g -fwrapv \
              -O2 \
              -Wall \
              -D_FORTIFY_SOURCE=2 \
              -g -fstack-protector \
              --param=ssp-buffer-size=4 \
              -Wformat \
              -Werror=format-security \
              $objdir/czigbee_wrap.o \
              $objdir/./src/czigbee.o \
              $objdir/./src/graph/calc_points.o \
              $objdir/./src/graph/cube.o \
              $objdir/./src/graph/sphere.o \
              $objdir/./src/graph/route-tree.o \
              $objdir/./src/io/serial.o \
              $objdir/./src/test/test.o \
              -o \
              build/lib.linux-x86_64-2.7/_czigbee.so


cp build/lib.linux-x86_64-2.7/* ../python/
echo "cp build/lib.linux-x86_64-2.7/* ../python/"

