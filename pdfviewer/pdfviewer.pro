TEMPLATE = app

QT += widgets

HEADERS += mainwindow.h

SOURCES += mainwindow.cpp\
           main.cpp

RESOURCES += pdfviewer.qrc

INCLUDEPATH += ../qpdflib

CONFIG(debug, debug|release) {
    LIBS += -L$$OUT_PWD/../qpdflib/debug
} else {
    LIBS += -L$$OUT_PWD/../qpdflib/release
}

win32:LIBS += qpdf.lib
unix:LIBS += qpdf.a

