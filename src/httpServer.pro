CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = httpServer
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
QT = core network


DEFINES += HTTPSERVER_LIBRARY
#DEFINES += QT_DEPRECATED_WARNINGS

include(../common.pri)


HEADERS += \
		HttpConnection.h \
		HttpResponse.h \
		HttpServer.h


SOURCES += \
		HttpConnection.cpp \
		HttpData.cpp \
		HttpRequest.cpp \
		HttpRequestRouter.cpp \
		HttpResponse.cpp \
		HttpServer.cpp \
		middleware/CORS.cpp \
		middleware/auth.cpp \
		middleware/getArray.cpp \
		middleware/getObject.cpp \
		middleware/verifyJson.cpp \
		util.cpp


#win32: LIBS += -lzlib
#unix: LIBS += -lz

#unix {
#	QMAKE_STRIP =
#
#	headers.path = /usr/local/include/httpServer
#	headers.files = $$HEADERS
#	target.path = /usr/local/lib
#	strip.path = /usr/local/lib
#	strip.commands = strip --strip-unneeded /usr/local/lib/$(TARGET)
#	strip.depends = install_headers install_target
#	INSTALLS += headers target strip
#}

