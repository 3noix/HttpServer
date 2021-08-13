CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}

TEMPLATE = app
TARGET = httpServerTest
CONFIG += c++17 console
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT = core network


#DEFINES += QT_DEPRECATED_WARNINGS

include(../common.pri)


HEADERS += RequestHandler.h
SOURCES += main.cpp RequestHandler.cpp


INCLUDEPATH += ../src
DEPENDPATH += ../src
LIBS += ../src/$$MODE/libhttpServer.a

