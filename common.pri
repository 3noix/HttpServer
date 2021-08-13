include(3rdparty/QtPromise/qtpromise.pri)
CONFIG -= c++11
CONFIG += c++17

QMAKE_CXXFLAGS += -Wno-maybe-uninitialized

INCLUDEPATH += $$(QT_DIR)/Tools/mingw810_32/lib/gcc/i686-w64-mingw32/8.1.0/include/c++
INCLUDEPATH += $$(QT_DIR)/Tools/mingw810_32/i686-w64-mingw32/include
LIBS += $$(QT_DIR)/Tools/mingw810_32/i686-w64-mingw32/lib/libz.a
