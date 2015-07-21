#ifndef WEBENGINEVIEW_H
#define WEBENGINEVIEW_H

#include <QWebEngineView>

class WebEngineView : public QWebEngineView
{
    Q_OBJECT
public:

    WebEngineView(QWidget *pParent = nullptr);

public slots:
    void invokeJavaScript(const QString &script);

protected:
    void contextMenuEvent(QContextMenuEvent *pEvent);

};

#endif // WEBENGINEVIEW_H
