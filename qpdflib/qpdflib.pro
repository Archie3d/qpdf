TEMPLATE = lib
TARGET = qpdf

CONFIG += dll

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
