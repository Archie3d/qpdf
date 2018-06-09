# QPdf
PDF viewer widget for Qt 5.

This is a wrapper of [pdf.js](https://mozilla.github.io/pdf.js) JavaScript PDF renderer using Qt WebEngine.

![Screenshot](https://raw.githubusercontent.com/Archie3d/qpdf/master/screenshot.png)

This qmake-based project defines two build targets: `qpdf` shared library, and an example PDF viewer (`pdfviewer`) based on `qpdf` library.
Should yoo want to integrate a PDF view into your project, you need to take `qpdf` library only, you do not need `pdfviewer` (though you may use it as inspirational example for your project). So you may copy `qpdflib` into your project and build it as a shared library to be linked with your code.

How to compile
--------------
* Make sure you have Qt 5.9.x or later installed. Earlier Qt versions are not supported.
* Open `qpdf.pro` project file in QtCreator
* Build and run

Open PDF files
--------------
`qpdf` library offers two ways to open PDF files:
* [QPdfWidget::loadData(const QByteArray& pdfData);](https://github.com/Archie3d/qpdf/blob/bc1be22d25f6f3fc8310cc87f6afcfee6e480d8d/qpdflib/qpdfwidget.h#L52)
* [QPdfWidget::loadFile(const QString& filePath);](https://github.com/Archie3d/qpdf/blob/bc1be22d25f6f3fc8310cc87f6afcfee6e480d8d/qpdflib/qpdfwidget.h#L46)

`loadData` method serializes PDF data as base64 string and injects it into JavaScript environment. This may fails however when loading huge PDF files

`loadFile` can PDFs of any size, however it faces cross-origin security restriction since it uses WebEngine's load URL method. In order to make this method work, you have to disable web security by passing `--disable-web-security` argument to your `QApplication` instance (see how its done in [pdfviwer example](https://github.com/Archie3d/qpdf/blob/bc1be22d25f6f3fc8310cc87f6afcfee6e480d8d/pdfviewer/main.cpp#L31)).

Debugging
---------
If something goes wrong, as sometimes it does, you may use Chromium debug console to assess the situation:
* Define QTWEBENGINE_REMOTE_DEBUGGING environment variable to activate WebEngine debug server, e.g.
  `QTWEBENGINE_REMOTE_DEBUGGING=0.0.0.0:9999`
* Launch your `qpdf`-based application
* Open Chrome or Chromium web browser and navigate to http://localhost:9999
* Select the running application link in the browser and you will be presented with a familiar web page inspection console.
