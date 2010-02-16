#!/bin/bash

version=`grep -m 1 VERSION src/resource.h | awk '{ print $3 }' | sed 's/"//g'`

make clean
cp -rf . ../govff-$version
cd ../govff-$version
mv Misc/* .
make
sudo checkinstall -D < input
mv *.deb ../
cd ../
rm -rf govff-$version
