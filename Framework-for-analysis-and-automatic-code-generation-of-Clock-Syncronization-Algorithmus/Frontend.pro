#-------------------------------------------------
#
# Project created by QtCreator 2017-07-31T14:34:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Frontend
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        frontend_class.cpp \
    backend/backend.cpp \
    backend/database.cpp \
    database_editor_class.cpp \
    backend/vectors.cpp

HEADERS += \
        frontend_class.h \
    backend/backend.h \
    backend/database.h \
    backend/variables_for_backend.h \
    database_editor_class.h \
    variables_for_frontend.h \
    sortabletablewidgetitem.h \
    backend/vectors.h

FORMS += \
        frontend_class.ui \
    database_editor.ui

LIBS += -lsqlite3
