TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

unix {
    DEFINES += RESOURCE_PATH='\'"/usr/share/ovff/"\''
    LIBS    += -L./lib/linux -lsqlite3 -luchardet
}

win32 {
    DEFINES += RESOURCE_PATH='""'
    CONFIG  -= debug_and_release
    HEADERS += sqlite3.h
    SOURCES += sqlite3.c
    RC_FILE += icon.rc
    LIBS    += -L./lib/windows -luchardet
}

HEADERS += FileMg.h SQLite_Manage.h resource.h utils.h
SOURCES += FileMg.cpp \
	   SQLite_Manage.cpp \
	   utils.cpp

# Input
ovff {
    TARGET = ovff
    CONFIG -= qt
    SOURCES += ovff.cpp
}

govff {
    TARGET = govff
    RESOURCES = resources.qrc
    HEADERS += ovffGui.h
    SOURCES += govff.cpp \
	       ovffGui.cpp
    TRANSLATIONS += translations/govff.ts
}
