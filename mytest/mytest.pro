CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = MyTest
CONFIG += c++17 console
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT = core network


include(../common.pri)

INCLUDEPATH += ../src
LIBS += ../src/$$MODE/libhttpServer.a


HEADERS +=  MyHttpServer.h


SOURCES +=  main.cpp MyHttpServer.cpp

