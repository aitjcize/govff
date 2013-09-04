#!/bin/bash

qmake=`which qmake-qt4`

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
	install -D -m 755 src/ovff \$(prefix)/bin/ovff
	install -D -m 755 src/govff \$(prefix)/bin/govff
	install -D -m 644 src/database/boshiamy.db \$(prefix)/share/ovff/database/boshiamy.db
	install -D -m 644 data/govff.png \$(prefix)/share/pixmaps/govff.png
	install -D -m 644 data/govff.desktop \$(prefix)/share/applications/govff.desktop

clean:              
	make -C src -f Makefile.ovff clean
	make -C src -f Makefile.govff clean

distclean:
	make -C src -f Makefile.ovff distclean qmake
	make -C src -f Makefile.govff distclean qmake
FILE

echo "Now run make."
