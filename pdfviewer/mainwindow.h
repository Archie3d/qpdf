#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QPdfWidget;

/**
 * @brief PDF viewer main window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow(QWidget *pParent = nullptr, Qt::WindowFlags flags = 0);

public slots:

    void loadFile(const QString &path);

private slots:

    void onOpenFile();

private:

    void createActions();
    void createToolBar();

    QAction *m_pOpenFileAction;
    QPdfWidget *m_pPdfWidget;
};

#endif // MAINWINDOW_H
