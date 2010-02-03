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
	make -f -C src Makefile.ovff distclean qmake
	make -f -C src Makefile.govff distclean qmake
