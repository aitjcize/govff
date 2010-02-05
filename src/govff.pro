TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

unix {
    DEFINES += RESOURCE_PATH='\'"/usr/share/ovff/"\''
    LIBS    += -lsqlite3
}

win32 {
    DEFIES += RESOURCE_PATH='""'
    CONFIG -= debug_and_release
    HEADERS += sqlite3.h
    SOURCES += sqlite3.c
    RC_FILE += icon.rc
}

# Input
ovff {
    TARGET = ovff
    CONFIG -= qt
    HEADERS += FileMg.h SQLite_Manage.h resource.h
    SOURCES += FileMg.cpp \
	       ovff.cpp \
	       SQLite_Manage.cpp
}

govff {
    TARGET = govff
    RESOURCES = resources.qrc
    HEADERS += FileMg.h ovffGui.h SQLite_Manage.h resource.h
    SOURCES += FileMg.cpp \
	       govff.cpp \
	       ovffGui.cpp \
	       SQLite_Manage.cpp
    TRANSLATIONS += translations/govff.ts
}
