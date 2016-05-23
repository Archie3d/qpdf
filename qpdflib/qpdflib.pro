TEMPLATE = lib
TARGET = qpdf

CONFIG += dll
CONFIG += c++11

QT += widgets\
      webengine\
      webenginecore\
      webenginewidgets

DEFINES += QPDFLIB_BUILD

HEADERS = webengineview.h\
          qpdfwidget.h

SOURCES = webengineview.cpp\
          qpdfwidget.cpp

RESOURCES += pdfview.qrc
