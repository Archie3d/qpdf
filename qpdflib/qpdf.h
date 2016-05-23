#ifndef QPDF_H
#define QPDF_H

#ifdef _MSC_VER

    #ifdef QPDFLIB_BUILD
    #   define QPDF_EXPORT  __declspec(dllexport)
    #else
    #   define QPDF_EXPORT  __declspec(dllimport)
    #endif

#else

    #define QPDF_EXPORT

#endif // _MSC_VER

#endif // QPDF_H
