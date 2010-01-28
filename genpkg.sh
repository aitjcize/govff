#!/bin/bash

version=`grep -m 1 VERSION ovff.cpp | awk '{ print $3 }' | sed 's/"//g'`

make clean
cp -rf . ../ovff-$version
cd ../ovff-$version
make
sudo checkinstall -D
mv *.deb ../
cd ../
rm -rf ovff-$version
