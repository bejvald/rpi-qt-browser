/*
* Project: QML-Browser
* Author: Björn Ejvald
* Date: 3.9.2013
*
* Copyright (c) 2013 Björn Ejvald. All rights reserved.
*
* This file is part of QML-Browser.
*
* QML-Browser is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* QML-Browser is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with QML-Browser. If not, see <http://www.gnu.org/licenses/>.
*/


#include <QApplication>
#include <QQuickView>
#include <QWebView>
#include <QQuickWindow>
#include "mainwindow.h"
#include <QWidget>

//#include "qtquick2applicationviewer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Create the root window
    MainWindow *browser = new MainWindow();

    QObject::connect(qApp,          SIGNAL(aboutToQuit()),
                     browser,   SLOT(cleanupSlot()));

    browser->resize(1280, 720);
    browser->move(320, 180);
    browser->show();

    return app.exec();


}
