# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = LabAssigment6

QT = core gui widgets

HEADERS = \
   $$PWD/omp.h \
   $$PWD/recount.h

SOURCES = \
   $$PWD/main.cpp \
   $$PWD/recount.cpp

INCLUDEPATH = \
    $$PWD/.

#DEFINES = 

QMAKE_CXXFLAGS += -fopenmp

LIBS += -fopenmp
