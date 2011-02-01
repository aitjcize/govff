#!/bin/bash

qmake=`which qmake`

echo -n "Generating makefiles... "
cd src
$qmake -config ovff -o Makefile.ovff
$qmake -config govff -o Makefile.govff
echo "Ok"
cd ..

cat << FILE > Makefile
prefix ?= /usr

all: ovff govff

ovff:
	make -C src -f Makefile.ovff
govff:              
	make -C src -f Makefile.govff

install:
	mkdir -p \$(prefix)/bin
	install -m 755 src/ovff \$(prefix)/bin/ovff
	install -m 755 src/govff \$(prefix)/bin/govff
	mkdir -p \$(prefix)/share/ovff/database
	install -m 644 src/database/boshiamy.db \$(prefix)/share/ovff/database/boshiamy.db
	mkdir -p \$(prefix)/share/pixmaps
	install -m 644 data/govff.png \$(prefix)/share/pixmaps/govff.png
	mkdir -p \$(prefix)/share/applications
	install -m 644 data/govff.desktop \$(prefix)/share/applications/govff.desktop

clean:              
	make -C src -f Makefile.ovff clean
	make -C src -f Makefile.govff clean

distclean:
	make -C src -f Makefile.ovff distclean qmake
	make -C src -f Makefile.govff distclean qmake
FILE

echo "Now run make."
