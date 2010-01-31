TEMPLATE = app
TARGET = govff
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += qt debug
HEADERS += FileMg.h ovffGui.h SQLite_Manage.h utils.h
SOURCES += FileMg.cpp govff.cpp ovff.cpp ovffGui.cpp SQLite_Manage.cpp utils.cpp
LIBS += -lsqlite3
