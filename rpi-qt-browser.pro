# Add more folders to ship with the application, here
folder_01.source = qml/rpi-qt-browser
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += quick core webkit multimedia network webkitwidgets declarative

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.



CONFIG += console
TARGET = rpi-qt-browser
#TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    bridgeobject.cpp


# Please do not modify the following two lines. Required for deployment.
#include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
#qtcAddDeployment()

# Installation path
target.path = /home/pi/rpi-qt-browser/bin

INSTALLS += target

RESOURCES += qmlmedia.qrc

HEADERS += \
    mainwindow.h \
    bridgeobject.h

OTHER_FILES += \
    LICENSE.txt \
    README.md
