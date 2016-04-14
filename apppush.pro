# qmake project generated by QMsDev
#
# General settings

TEMPLATE = app
#CONFIG  += qt warn_off
TARGET  += apppush
INCLUDEPATH += . ../include ../../include 
#DESTDIR = ../bin
#OBJECTS_DIR = ../obj

# Input

FORMS =  \
		mainform.ui


SOURCES =  \
		globalobject.cpp \
		main.cpp \
		mainformimpl.cpp \
                dealDayENERGYDataThread.cpp \
                dealENERGYDataThread.cpp \
                dealMainServiceThread.cpp \
                dealMinTableDataThread.cpp \
                dealVolDataThread.cpp \
	        SQLFuncPublic.cpp 	

HEADERS =  \
		globalobject.h \
		mainformimpl.h \
                ui_mainform.h
                dealDayENERGYDataThread.h \
                dealENERGYDataThread.h \
                dealMainServiceThread.h \
                dealMinTableDataThread.h \
                dealVolDataThread.h \
		SQLFuncPublic.h


QT       += core gui widgets


