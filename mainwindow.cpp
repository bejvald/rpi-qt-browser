#include "mainwindow.h"
#include <QApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDesktopWidget>
#include <QtWebKit>
#include <QtNetwork>
#include <QWebView>
#include <QQuickWindow>
#include <QQuickItem>
#include <QWebFrame>

MainWindow::MainWindow() : QWidget()
{
    //Initiate

    progress = 0;

    mediaView = new QQuickView(this->windowHandle());
    browserView= new QWebView(this);

    mediaView->setSource(QUrl("qrc:///qml/videoPlayer.qml"));
    bridge= new bridgeObject(mediaView->rootObject());


    //Resize views
    //TODO: Make these fetch the TV-size
    mediaView->setResizeMode(QQuickView::SizeRootObjectToView);
    mediaView->resize(1920, 1080);

    browserView->resize(800, 600);
    browserView->move(500, 200);

    //Make the background of the mediawindow transparent
    QSurfaceFormat format;
    format.setAlphaBufferSize(8);
    qDebug() << format.hasAlpha();
    mediaView->setFormat(format);

    QColor color;
    color.setRedF(0.0);
    color.setGreenF(0.0);
    color.setBlueF(0.0);
    color.setAlphaF(0.0);
    mediaView->setColor(color);
    mediaView->setClearBeforeRendering(true);

    //Make the background of the root window transparent
    setAttribute(Qt::WA_TranslucentBackground, true);

    //Connect the signals
    connect(browserView, SIGNAL(urlChanged(const QUrl &)), SLOT(urlChanged(const QUrl &)));
    connect(browserView, SIGNAL(loadStarted()), SLOT(loadStarted()));

    //Show the screens
    mediaView->show();
    browserView->show();

    browserView->setUrl(QUrl("file:///home/pi/test.html"));

}

//WebView implementations

void MainWindow::centerFixedSizeWindow()
{
    quint16 windowWidth = mainSettings->value("view/fixed-width").toUInt();
    quint16 windowHeight = mainSettings->value("view/fixed-height").toUInt();

    quint16 screenWidth = QApplication::desktop()->screenGeometry().width();
    quint16 screenHeight = QApplication::desktop()->screenGeometry().height();

    qDebug() << "Screen size: " << screenWidth << "x" << screenHeight;

    quint16 x = 0;
    quint16 y = 0;

    if (mainSettings->value("view/fixed-centered").toBool()) {
        x = (screenWidth - windowWidth) / 2;
        y = (screenHeight - windowHeight) / 2;
    } else {
        x = mainSettings->value("view/fixed-x").toUInt();
        y = mainSettings->value("view/fixed-y").toUInt();
    }

    qDebug() << "Move window to: (" << x << ";" << y << ")";

    move ( x, y );
    setFixedSize( windowWidth, windowHeight );

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Q:
        if (int(event->modifiers()) == Qt::CTRL) {
            qDebug() << "Key Ctrl+Q was pressed";
            //clearCacheOnExit();
            QApplication::exit(0);
        }
    case Qt::Key_F2:
        qDebug() << "Key F2 was pressed";
        bridge->setFullscreen();
        break;
    case Qt::Key_F3:
        qDebug() << "Key F3 was pressed";
        bridge->play(1);
        break;
    case Qt::Key_F4:
        qDebug() << "Key F4 was pressed";
        bridge->pause();
        break;
    case Qt::Key_F5:
        qDebug() << "Key F5 was pressed";
        browserView->reload();
        break;
    case Qt::Key_F11:
        qDebug() << "Key F11 was pressed";
        break;

    }
}

void MainWindow::urlChanged(const QUrl &url)
{

    qDebug() << "URL changes: " << url.toString();

    //Add the javascript-webkit-brigdge to each page
    QWebFrame *frame=browserView->page()->mainFrame();
    frame->addToJavaScriptWindowObject("bridge", bridge);

    //Handle opening of video-links
    QString uri=url.toString();

    if(uri.contains(".mp4") ||
       uri.contains(".avi")){

        qDebug() << "Url contains mp4!";
        //browserView->stop(); //Seg-faults
        bridge->open(uri);
    }
}
void MainWindow::loadStarted()
{
    qDebug() << "Load started";
}

void MainWindow::cleanupSlot()
{
    qDebug() << "Cleanup Slot (application exit)";
    //clearCacheOnExit();
    QWebSettings::clearMemoryCaches();
}
