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

#include <QFile>
#include <QVBoxLayout>
#include "webengineview.h"
#include "qpdfwidget.h"

// class private members
struct QPdfWidgetPrivate
{
    WebEngineView *pWebEngineView;
    bool ready;
    QByteArray pdfData;
};

QPdfWidget::QPdfWidget(QWidget *pParent)
    : QWidget(pParent)
{
    m = new QPdfWidgetPrivate;
    m->pWebEngineView = new WebEngineView();
    connect(m->pWebEngineView, &WebEngineView::loadFinished, this, &QPdfWidget::onLoadFinished);
    m->ready = false;

    // Initialize pdf.js viewer
    QUrl url = QUrl::fromUserInput("qrc:/pdfview/viewer.html");
    m->pWebEngineView->setUrl(url);    

    // widget layout
    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->setMargin(0);
    pLayout->addWidget(m->pWebEngineView);
    setLayout(pLayout);
}

QPdfWidget::~QPdfWidget()
{
    delete m;
}

bool QPdfWidget::loadFile(const QString &path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        m->pdfData = file.readAll();
        file.close();
        renderPdf();
        return true;
    }

    return false;
}

void QPdfWidget::loadData(const QByteArray &data)
{
    m->pdfData = data;
    renderPdf();
}

void QPdfWidget::setPage(int page)
{
    QString script = QString("PDFViewerApplication.page = %1")
                        .arg(page);
    m->pWebEngineView->invokeJavaScript(script);
}

int QPdfWidget::page() const
{
    QVariant res = m->pWebEngineView->invokeJavaScriptAndWaitForResult("PDFViewerApplication.page");
    if (res.isValid()) {
        return res.toInt();
    }
    return 0;
}

int QPdfWidget::pagesCount() const
{
    QVariant res = m->pWebEngineView->invokeJavaScriptAndWaitForResult("PDFViewerApplication.pagesCount");
    if (res.isValid()) {
        return res.toInt();
    }
    return 0;
}

void QPdfWidget::rotatePages(int degrees)
{
    QString script = QString("PDFViewerApplication.rotatePages(%1)")
                        .arg(degrees);
    m->pWebEngineView->invokeJavaScript(script);
}

void QPdfWidget::zoomIn(int ticks)
{
    QString script = QString("PDFViewerApplication.zoomIn(%1)").arg(ticks);
    m->pWebEngineView->invokeJavaScript(script);
}

void QPdfWidget::zoomOut(int ticks)
{
    QString script = QString("PDFViewerApplication.zoomOut(%1)").arg(ticks);
    m->pWebEngineView->invokeJavaScript(script);
}

void QPdfWidget::zoomReset(qreal scale)
{
    QString script = QString("PDFViewerApplication.pdfViewer.currentScaleValue=%1").arg(scale);
    m->pWebEngineView->invokeJavaScript(script);
}

void QPdfWidget::showDocumentProperties()
{
    m->pWebEngineView->invokeJavaScript("PDFViewerApplication.pdfDocumentProperties.open()");
}

void QPdfWidget::setFindBarVisible(bool v)
{
    QString script = QString("PDFViewerApplication.findBar.%1()")
            .arg(v ? "open" : "close");
    m->pWebEngineView->invokeJavaScript(script);
}

void QPdfWidget::findNext(const QString &text)
{
    if (!text.isEmpty()) {
        setFindFieldText(text);
    }

    m->pWebEngineView->invokeJavaScript("PDFViewerApplication.findBar.dispatchEvent('again', false);");
}

void QPdfWidget::findPrevious(const QString &text)
{
    if (!text.isEmpty()) {
        setFindFieldText(text);
    }

    m->pWebEngineView->invokeJavaScript("PDFViewerApplication.findBar.dispatchEvent('again', true);");
}

int QPdfWidget::findResultsCount() const
{
    QVariant res = m->pWebEngineView->invokeJavaScriptAndWaitForResult("PDFViewerApplication.findController.matchCount");
    if (res.isValid()) {
        return res.toInt();
    }
    return 0;
}

void QPdfWidget::navigateTo(const QString &dest)
{
    QString escapedDest = dest;
    escapedDest.replace("\"", "\\\"");
    QString script = QString("PDFViewerApplication.pdfLinkService.navigateTo(\"%1\")")
            .arg(escapedDest);
    m->pWebEngineView->invokeJavaScript(script);
}

QStringList QPdfWidget::getDestinations() const
{
    return m->pWebEngineView->fetchPdfDocumentDestinations();
}

QWebEngineView* QPdfWidget::internalWebEngineView() const
{
    return dynamic_cast<QWebEngineView*>(m->pWebEngineView);
}

void QPdfWidget::onLoadFinished(bool status)
{
    if (!status) {
        qCritical() << "Unable to initialize the web view";
        return;
    }

    m->ready = true;
    if (!m->pdfData.isEmpty()) {
        renderPdf();
    }
}

void QPdfWidget::renderPdf()
{
    if (!m->ready) {
        return;
    }

    m->pdfData = m->pdfData.toBase64();
    QString script = QString("showPdfFile('%1')")
                        .arg(QString::fromUtf8(m->pdfData));

    m->pWebEngineView->invokeJavaScript(script);

    // Clear pdf data
    m->pdfData.clear();
}

void QPdfWidget::setFindFieldText(const QString &text)
{
    // Reset find controller.
    m->pWebEngineView->invokeJavaScriptAndWaitForResult("PDFViewerApplication.findController.reset()");

    // Fill-in the find field.
    QString escapedText = text;
    escapedText.replace("\"", "\\\"");
    QString script = QString("PDFViewerApplication.findBar.findField.value=\"%1\"")
            .arg(escapedText);
    m->pWebEngineView->invokeJavaScript(script);
}
