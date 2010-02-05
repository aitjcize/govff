#!/bin/bash

qmake=`which qmake`

echo -n "Generating makefiles... "
cd src
$qmake -config ovff -o Makefile.ovff
$qmake -config govff -o Makefile.govff
echo "Ok"
cd ..

cat << FILE > Makefile
all: ovff govff

ovff:
	make -C src -f Makefile.ovff
govff:              
	make -C src -f Makefile.govff

install:
	cp -f src/ovff /usr/bin
	cp -f src/govff /usr/bin
	mkdir -p /usr/share/ovff
	cp -rf src/database /usr/share/ovff
	cp -f data/govff.png /usr/share/pixmaps
	cp -f data/govff.desktop /usr/share/applications

clean:              
	make -C src -f Makefile.ovff clean
	make -C src -f Makefile.govff clean

distclean:
	make -C src -f Makefile.ovff distclean qmake
	make -C src -f Makefile.govff distclean qmake
FILE

echo "Now run make."
