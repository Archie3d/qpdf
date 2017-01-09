/*
                          qpdf

    Copyright (C) 2015 Arthur Benilov,
    arthur.benilov@gmail.com
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    Lesser General Public License for more details.
*/

#ifndef PDFJSBRIDGE_H
#define PDFJSBRIDGE_H

#include <QWebEngineView>
#include <QSemaphore>

class PdfJsBridge : public QWebEngineView
{
    Q_OBJECT
public:

    PdfJsBridge(QWidget *pParent = nullptr);
    ~PdfJsBridge();

    void invokeJavaScript(const QString &script);

    QVariant invokeJavaScriptAndWaitForResult(const QString &script);

    QStringList fetchPdfDocumentDestinations();

    void close();

signals:

    void pdfDocumentloaded();

public slots:

    void jsInitialized();
    void jsReportDestinations(const QStringList &destinations);
    void jsLoaded();
    void jsClosed();

protected:
    void contextMenuEvent(QContextMenuEvent *pEvent);

private slots:

    void onLoadFinished(bool ok);

private:


    void establishWebChannel();

    QWebChannel *m_pWebChannel;
    QSemaphore m_pdfDestinationsSema;

    QStringList m_pdfDocumentDestinations;

    QSemaphore m_pdfCloseSema;

};

#endif // PDFJSBRIDGE_H
