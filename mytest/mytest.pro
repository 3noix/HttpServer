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


INCLUDEPATH += $$(PROG_DIR)/QtPromise/include
#INCLUDEPATH += $$(PROG_DIR)/QtPromise/src
QMAKE_CXXFLAGS += -Wno-maybe-uninitialized

INCLUDEPATH += ../src
LIBS += ../src/release/libhttpServer.a

#INCLUDEPATH += $$(QT_DIR)/Tools/mingw810_32/lib/gcc/i686-w64-mingw32/8.1.0/include/c++
#INCLUDEPATH += $$(QT_DIR)/Tools/mingw810_32/i686-w64-mingw32/include
#LIBS += $$(QT_DIR)/Tools/mingw810_32/i686-w64-mingw32/lib/libz.a


HEADERS +=  MyHttpServer.h


SOURCES +=  main.cpp MyHttpServer.cpp

