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
