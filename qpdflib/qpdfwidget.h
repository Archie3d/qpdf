#ifndef QPDFWIDGET_H
#define QPDFWIDGET_H

#include <QWidget>
#include "qpdf.h"

struct QPdfWidgetPrivate;

/**
 * @brief PDF visualizationm widget.
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

private slots:

    void onLoadFinished(bool status);
    void renderPdf();

private:

    /// Private members.
    QPdfWidgetPrivate *m;
};

#endif // QPDFWIDGET_H
