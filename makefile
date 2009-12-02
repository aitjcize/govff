objects = ovff.o Ovff_Manage.o FileMg.o itoa.o

CFLAGS = -lsqlite3 -Wall

ovff: $(objects)
	g++ -o ovff $(objects) $(CFLAGS)

clean:
	rm -rf $(objects) ovff
