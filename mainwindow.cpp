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
    //Initiate views
    progress = 0;

    mediaView = new QQuickView(this->windowHandle());
    browserView= new QWebView(this);

    //Set QML and initiate the webkit-bridge
    mediaView->setSource(QUrl("qrc:///qml/videoPlayer.qml"));
    rpi= new bridgeObject(mediaView->rootObject());

    //Resize views
    //TODO: Make these fetch the TV-size
    mediaView->setResizeMode(QQuickView::SizeRootObjectToView);

    mediaView->resize(1280, 720);
    browserView->resize(1280, 720);

    //Make the background of the root- and browserwindow transparent
    setAttribute(Qt::WA_TranslucentBackground, true);
    setStyleSheet("background-color: rgba(0,0,0,1%)");
    browserView->setAttribute(Qt::WA_TranslucentBackground, true);

    //Connect the signals
    connect(browserView, SIGNAL(urlChanged(const QUrl &)), SLOT(urlChanged(const QUrl &)));
    connect(browserView, SIGNAL(loadStarted()), SLOT(loadStarted()));

    homePage=QUrl("http://devcentre.hibox.fi/dlx");

    //Show the screens
    mediaView->show();
    browserView->show();

    //Url-loading triggered from main.cpp

}

//WebView implementations

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Q:
        if (int(event->modifiers()) == Qt::CTRL)
        {
            qDebug() << "Key Ctrl+Q was pressed";
            //clearCacheOnExit();
            QApplication::exit(0);
        }
    case Qt::Key_F5:
        qDebug() << "Key F5 was pressed";
        browserView->reload();
        break;
    }
}

void MainWindow::loadUrl(QUrl url)
{
    //Adding bridgeobject here doesn't work
    qDebug() << "Loading Url: " + url.toString();
    browserView->setUrl(url);
}

void MainWindow::cleanupSlot()
{
    qDebug() << "Cleanup Slot (application exit)";
    //clearCacheOnExit();
    QWebSettings::clearMemoryCaches();
}

void MainWindow::urlChanged(const QUrl &url)
{
    qDebug() << "URL changes: " << url.toString();

    QWebFrame *frame=browserView->page()->mainFrame();
    frame->addToJavaScriptWindowObject("rpi", rpi);

    //Handle opening of video-links
    QString uri=url.toString();

    if(uri.contains(".mp4") ||
       uri.contains(".avi")){

        qDebug() << "Url contains mp4!";
        //browserView->stop(); //Seg-faults
        rpi->open(uri);
    }
}

void MainWindow::loadStarted()
{
    //Adding bridgeobject here doesn't work
    qDebug() << "Load started";
}

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

