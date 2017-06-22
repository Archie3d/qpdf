TEMPLATE = subdirs

SUBDIRS = qpdflib\
          pdfviewer

pdfviewer.depends = qpdflib
