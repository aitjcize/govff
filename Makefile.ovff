TARGET 	 = ovff
CXXFLAGS = -lsqlite3 -O2 -Wall -g

objects = ovff.o SQLite_Manage.o FileMg.o utils.o

.cpp:
	$(CXX) -c $(CXXFLAGS)


ovff: $(objects)
	$(CXX) -o $(TARGET) $(objects) $(CXXFLAGS)

install:
	mkdir -p /usr/share/ovff
	cp ovff /usr/bin
	cp boshiamy_t.db /usr/share/ovff

clean:
	rm -rf $(objects)

distclean:
	rm -rf $(objects) $(TARGET)
