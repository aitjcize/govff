TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

unix {
    DEFINES += RESOURCE_PATH='\'"/usr/share/ovff/"\''
    LIBS    += -lsqlite3 lib/linux/libchardetect.a
}

win32 {
    DEFINES += RESOURCE_PATH='""'
    CONFIG  -= debug_and_release
    HEADERS += sqlite3.h
    SOURCES += sqlite3.c
    RC_FILE += icon.rc
    LIBS    += lib/windows/libchardetect.a
}

HEADERS += FileMg.h SQLite_Manage.h resource.h utils.h chardetect.h
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
