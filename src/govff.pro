TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

unix {
    DEFINES += RESOURCE_PATH='\'"/usr/share/ovff/"\''
}

win32 {
    DEFIES += RESOURCE_PATH='""'
}

# Input
ovff {
    TARGET = ovff
    CONFIG -= qt
    HEADERS += FileMg.h SQLite_Manage.h resource.h
    SOURCES += FileMg.cpp \
	       ovff.cpp \
	       SQLite_Manage.cpp
    LIBS	+= -lsqlite3
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
    LIBS	+= -lsqlite3
}
