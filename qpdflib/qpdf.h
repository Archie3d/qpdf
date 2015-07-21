#ifndef QPDF_H
#define QPDF_H

#ifdef QPDFLIB_BUILD
#   define QPDF_EXPORT  __declspec(dllexport)
#else
#   define QPDF_EXPORT  __declspec(dllimport)
#endif

#endif // QPDF_H
