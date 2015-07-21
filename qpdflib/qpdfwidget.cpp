#include <QDebug>
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
