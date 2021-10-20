include(3rdparty/QtPromise/qtpromise.pri)
CONFIG -= c++11
CONFIG += c++17

# a lot of maybe-uninitialized warnings from QtPromise
QMAKE_CXXFLAGS += -Wno-maybe-uninitialized

win32: LIBS += ../3rdparty/zlib/lib/libz.a
unix: LIBS += -lz
