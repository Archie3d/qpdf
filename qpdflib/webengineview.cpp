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

#include <QApplication>
#include <QWebChannel>
#include <QContextMenuEvent>
#include <QSemaphore>
#include "webengineview.h"

WebEngineView::WebEngineView(QWidget *pParent)
    : QWebEngineView(pParent)
{
    m_pWebChannel = new QWebChannel(this);

    connect(this, &QWebEngineView::loadFinished, this, &WebEngineView::onLoadFinished);
}

void WebEngineView::invokeJavaScript(const QString &script)
{
    QWebEnginePage *pPage = page();
    if (pPage != nullptr) {
        pPage->runJavaScript(script);
    }
}

QVariant WebEngineView::invokeJavaScriptAndWaitForResult(const QString &script)
{
    QVariant result;
    QWebEnginePage *pPage = page();
    if (pPage != nullptr) {

        QSemaphore waitSemaphore;
        pPage->runJavaScript(script, [&result, &waitSemaphore](const QVariant &res) {
            result = res;
            waitSemaphore.release();
        });

        while (!waitSemaphore.tryAcquire()) {
            qApp->processEvents();
        }
    }

    return result;
}

QStringList WebEngineView::fetchPdfDocumentDestinations()
{
    m_pdfDocumentDestinations.clear();

    invokeJavaScript("qpdf_FetchDestinations();");

    while (!m_pdfDestinationsSema.tryAcquire()) {
        qApp->processEvents();
    }

    return m_pdfDocumentDestinations;
}

void WebEngineView::jsInitialized()
{
    // Web view has been initialized
}

void WebEngineView::jsReportDestinations(const QStringList &destinations)
{
    m_pdfDocumentDestinations = destinations;
    m_pdfDestinationsSema.release();
}

void WebEngineView::contextMenuEvent(QContextMenuEvent *pEvent)
{
    // Disable context menu completely
    pEvent->ignore();
}

void WebEngineView::onLoadFinished(bool ok)
{
    if (ok) {
        establishWebChannel();
    }
}

void WebEngineView::establishWebChannel()
{
    QWebEnginePage *pPage = page();
    if (pPage != nullptr) {
        pPage->setWebChannel(m_pWebChannel);
        m_pWebChannel->registerObject("qpdfview", this);

        pPage->runJavaScript("qpdf_Initialize();");
    }
}
