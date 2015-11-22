TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp \
    point.cpp \
    face.cpp \
    maillage.cpp \
    pointspherique.cpp \
    bin.cpp

HEADERS += \
    point.h \
    face.h \
    maillage.h \
    pointspherique.h \
    bin.h

RESOURCES += \
    tmoche.qrc

