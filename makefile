objects = ovff.o Ovff_Manage.o FileMg.o itoa.o

CFLAGS = -lsqlite3 -Wall

ovff: $(objects)
	g++ -o ovff $(objects) $(CFLAGS)
install:
	mkdir -p /usr/share/ovff
	cp ovff /usr/bin
	cp boshiamy_t.db /usr/share/ovff

clean:
	rm -rf $(objects) ovff
