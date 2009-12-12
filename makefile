objects = ovff.o SQLite_Manage.o FileMg.o utils.o

CFLAGS = -lsqlite3 -Wall

ovff: $(objects)
	g++ -o ovff $(objects) $(CFLAGS)
install:
	mkdir -p /usr/share/ovff
	cp ovff /usr/bin
	cp boshiamy_t.db /usr/share/ovff

clean:
	rm -rf $(objects) ovff
