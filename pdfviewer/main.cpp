#include <QApplication>
#include <QTimer>
#include "mainwindow.h"

// This is a simple application that demonstrated the QPdfWidget usage.
// The main function here can accept a single (optional) argument to trigger
// the PDF file loading from the command prompt.

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    if (argc > 1) {
        // Load file provided as an argument
        QString filePath = QString::fromLatin1(argv[1]);
        QTimer::singleShot(0, [filePath, &mainWindow]() {
            mainWindow.loadFile(filePath);
        });
    }

    return app.exec();
}
