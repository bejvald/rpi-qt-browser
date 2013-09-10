#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtGui>
#include <QMainWindow>
#include <QtNetwork>
#include <QtWebKit>
#include <qquickview.h>
#include <QWebView>
#include <bridgeobject.h>
#include <QUrl>


class MainWindow : public QWidget
{
    Q_OBJECT

public:

    explicit MainWindow();

    void keyPressEvent(QKeyEvent *event);

    QUrl homePage;
    void loadUrl(QUrl url);
    
protected slots:

    void cleanupSlot();
    void urlChanged(const QUrl &);
    void loadStarted();

protected:

    void centerFixedSizeWindow();

private:

    QWebView *browserView;
    QQuickView *mediaView;
    QSettings *mainSettings;
    QKeyEvent * eventExit;
    bridgeObject *rpi; //The javascript-webkit bridge object

    int progress;
    
};

#endif // MAINWINDOW_H
