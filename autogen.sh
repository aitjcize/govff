#!/bin/bash

QMAKE=`which qmake-qt4`

echo -n "Generating makefiles... "
cd src
$QMAKE -config ovff -o Makefile.ovff
$QMAKE -config govff -o Makefile.govff
echo "Ok"
cd ..

cat << FILE > Makefile
PREFIX ?= /usr

all: ovff govff

ovff:
	make -C src -f Makefile.ovff
govff:              
	make -C src -f Makefile.govff

install:
	install -D -m 755 src/ovff \$(PREFIX)/bin/ovff
	install -D -m 755 src/govff \$(PREFIX)/bin/govff
	install -D -m 644 src/database/boshiamy.db \$(PREFIX)/share/ovff/database/boshiamy.db
	install -D -m 644 data/govff.png \$(PREFIX)/share/pixmaps/govff.png
	install -D -m 644 data/govff.desktop \$(PREFIX)/share/applications/govff.desktop

clean:              
	make -C src -f Makefile.ovff clean
	make -C src -f Makefile.govff clean

distclean:
	make -C src -f Makefile.ovff distclean qmake
	make -C src -f Makefile.govff distclean qmake
FILE

echo "Now run make."
