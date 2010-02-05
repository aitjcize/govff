#!/bin/bash

version=`grep -m 1 VERSION src/ovff.cpp | awk '{ print $3 }' | sed 's/"//g'`

make clean
cp -rf . ../govff-$version
cd ../govff-$version
make
sudo checkinstall -D < input
mv *.deb ../
cd ../
rm -rf govff-$version
