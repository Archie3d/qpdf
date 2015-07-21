#include <QContextMenuEvent>
#include "webengineview.h"

WebEngineView::WebEngineView(QWidget *pParent)
    : QWebEngineView(pParent)
{
}

void WebEngineView::invokeJavaScript(const QString &script)
{
    QWebEnginePage *pPage = page();
    if (pPage != nullptr) {
        pPage->runJavaScript(script, [](const QVariant &res) {
            Q_UNUSED(res);
        });
    }
}

void WebEngineView::contextMenuEvent(QContextMenuEvent *pEvent)
{
    // Disable context menu completely
    pEvent->ignore();
}
