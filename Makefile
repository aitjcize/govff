CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -lsqlite3 -lQtGui -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = FileMg.cpp \
		govff.cpp \
		ovff.cpp \
		ovffGui.cpp \
		SQLite_Manage.cpp \
		utils.cpp moc_ovffGui.cpp
OBJECTS       = FileMg.o \
		govff.o \
		ovffGui.o \
		SQLite_Manage.o \
		utils.o \
		moc_ovffGui.o
OBJECTS2      = FileMg.o \
		ovff.o \
		ovffGui.o \
		SQLite_Manage.o \
		utils.o \
		moc_ovffGui.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		govff.pro
QMAKE_TARGET  = govff
DESTDIR       = 
TARGET        = govff
TARGET2       = ovff

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS) $(OBJECTS2) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	$(LINK) $(LFLAGS) -o $(TARGET2) $(OBJECTS2) $(OBJCOMP) $(LIBS)

Makefile: govff.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile govff.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile govff.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/govff1.0.0 || $(MKDIR) .tmp/govff1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/govff1.0.0/ && $(COPY_FILE) --parents FileMg.h ovffGui.h SQLite_Manage.h utils.h .tmp/govff1.0.0/ && $(COPY_FILE) --parents FileMg.cpp govff.cpp ovff.cpp ovffGui.cpp SQLite_Manage.cpp utils.cpp .tmp/govff1.0.0/ && (cd `dirname .tmp/govff1.0.0` && $(TAR) govff1.0.0.tar govff1.0.0 && $(COMPRESS) govff1.0.0.tar) && $(MOVE) `dirname .tmp/govff1.0.0`/govff1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/govff1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS) $(OBJECTS2)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET2)

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_ovffGui.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_ovffGui.cpp
moc_ovffGui.cpp: FileMg.h \
		ovffGui.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ovffGui.h -o moc_ovffGui.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

FileMg.o: FileMg.cpp FileMg.h \
		utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FileMg.o FileMg.cpp

govff.o: govff.cpp ovffGui.h \
		FileMg.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o govff.o govff.cpp

ovff.o: ovff.cpp FileMg.h \
		SQLite_Manage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ovff.o ovff.cpp

ovffGui.o: ovffGui.cpp ovffGui.h \
		FileMg.h \
		SQLite_Manage.h \
		../lib/sdebug.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ovffGui.o ovffGui.cpp

SQLite_Manage.o: SQLite_Manage.cpp SQLite_Manage.h \
		FileMg.h \
		utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SQLite_Manage.o SQLite_Manage.cpp

utils.o: utils.cpp utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o utils.o utils.cpp

moc_ovffGui.o: moc_ovffGui.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ovffGui.o moc_ovffGui.cpp

####### Install

install:
	mkdir /usr/share/ovff
	cp -f boshiamy_t.db /usr/share/ovff
	cp -f $(TARGET) $(TARGET2) /usr/bin

uninstall:   FORCE

FORCE:

