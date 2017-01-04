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

#ifndef QPDFWIDGET_H
#define QPDFWIDGET_H

#include <QWidget>
#include "qpdf.h"

class QWebEngineView;

struct QPdfWidgetPrivate;

/**
 * @brief PDF visualization widget.
 *
 * This class represents a widget used to visualize a pdf file.
 * It handles pdf file loading but also accepts raw data (byte array)
 * to be interpreted as a pdf.
 */
class QPDF_EXPORT QPdfWidget : public QWidget
{
    Q_OBJECT
public:

    QPdfWidget(QWidget *pParent = nullptr);
    ~QPdfWidget();

    /**
     * @brief Load and display a pdf file.
     * @param path Absolute path to a pdf file.
     * @return true if loaded Ok, false if unable to load.
     */
    bool loadFile(const QString &path);

    /**
     * @brief Load raw pdf data.
     * @param data PDF data.
     */
    void loadData(const QByteArray &data);

    /**
     * @brief Set current page.
     *
     * This will make the viewer to navigate to a specific
     * page of the document.
     *
     * This method does not change the view when trying to navigate
     * outside of the document.
     *
     * @param page Page number.
     */
    void setPage(int page);

    /**
     * @brief Returns current page viewed.
     * @return Current page.
     */
    int page() const;

    /**
     * @brief Returns total number of pages in the document.
     * @return Total number of pages.
     */
    int pagesCount() const;

    /**
     * @brief Rotate all pages.
     *
     * Rotate current view by given angle.
     *
     * @param degrees Rotation delta, divisible by 90.
     */
    void rotatePages(int degrees);

    /**
     * @brief Show PDF document properties pop-up window.
     */
    void showDocumentProperties();

    /**
     * @brief Set find bar visibility.
     * @param v true to show the find bar, false to hide it.
     */
    void setFindBarVisible(bool v);

    /**
     * @brief findNext Find text in the document.
     *
     * This method searches the text from the current view position
     * till the end of the document. Found text will be highlighted.
     *
     * @param text Text to find.
     */
    void findNext(const QString &text = QString());

    /**
     * @brief findPrevious Find text in the document.
     *
     * This method searches the text from the current view position
     * up to the beginning of the document. Found text will be highlighted.
     *
     * @param text Text to find.
     */
    void findPrevious(const QString &text = QString());

    /**
     * @brief Returns the number of matches found.
     *
     * @note This function will return zero when called
     * immediately after \ref findNext or \ref findPrevious.
     * This is due to the ascynchronous nature of the find controller.
     * One may introduce a small delay to make sure this function returns
     * a valid result.
     *
     * @return Number of found results.
     */
    int findResultsCount() const;

    /**
     * @brief Returns pointer to underlying web view.
     *
     * @note Using this method exposes implementation details and is not recommended.
     *
     * @return Pointer to internal web view.
     */
    QWebEngineView* internalWebEngineView() const;

private slots:

    void onLoadFinished(bool status);
    void renderPdf();

private:

    void setFindFieldText(const QString &text);

    /// Private members.
    QPdfWidgetPrivate *m;
};

#endif // QPDFWIDGET_H
