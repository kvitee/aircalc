QT += core widgets gui

TEMPLATE = app
TARGET = bin/aircalc
INCLUDEPATH += src/include/

HEADERS += $$files(src/include/*.hpp, true)
SOURCES += $$files(src/*.cpp, true)

RESOURCES += resources.qrc