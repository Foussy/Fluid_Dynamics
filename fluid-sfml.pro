TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-audio
LIBS += -lsfml-graphics
LIBS += -lsfml-network
LIBS += -lsfml-window
LIBS += -lsfml-system

SOURCES += \
        field.cpp \
        fluid.cpp \
        main.cpp

HEADERS += \
    boundary.h \
    field.h \
    fluid.h
