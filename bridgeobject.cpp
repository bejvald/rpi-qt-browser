#include "bridgeobject.h"
#include <QQuickItem>
#include <QMetaObject>

bridgeObject::bridgeObject(QQuickItem *parent) : QObject()
{
    root=parent;
}
//Hibox API

int bridgeObject::getVolume(){

    float vol=root->property("targetVolume").toFloat();
    return int(vol*100);
}

void bridgeObject::setVolume(int volume){
    float targetVolume=volume/100.0;
    root->setProperty("targetVolume", targetVolume);
    QMetaObject::invokeMethod(root, "setVolume");
}

bool bridgeObject::isMuted(){
    return root->property("muteStatus").toBool();
}

void bridgeObject::mute(bool muteStatus){
    root->setProperty("muteStatus", muteStatus);
    QMetaObject::invokeMethod(root, "mute");
}

void bridgeObject::open(QString uri){
    QUrl fileName(uri);
    root->setProperty("fileName", fileName);
    QMetaObject::invokeMethod(root, "init");
}

void bridgeObject::play(int speed){
    root->setProperty("playSpeed", speed);
    QMetaObject::invokeMethod(root, "play");
}

void bridgeObject::pause(){
    QMetaObject::invokeMethod(root, "pause");
}

void bridgeObject::setPosition(int x, int y, int width, int height){
    root->setProperty("targetX", x);
    root->setProperty("targetY", y);
    root->setProperty("targetWidth", width);
    root->setProperty("targetHeight", height);
    QMetaObject::invokeMethod(root, "setTargetPosition");
}

void bridgeObject::setFullscreen(){
    QMetaObject::invokeMethod(root, "setFullscreen");
}
void bridgeObject::reboot(){
    system("/sbin/reboot -f");
}

QString bridgeObject::getSerialNumber(){
    QString serial;
    QFile file("/proc/cpuinfo");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Could not open file for reading";
        serial=QString("Error: File could not open");
        return serial;
    }
    QTextStream in(&file);
    for (int i=0; i<12; i++) {
        QString line = in.readLine();
        QStringList wordLine = line.split(":");

        if(line.contains("Serial")){
            serial=wordLine.at(1);
            serial.replace(" ", "");
            qDebug() << "bridge.serial: " + serial;
            file.close();
        }
        else
            serial=QString("File not found");
    }
    file.close();

    return serial;
}


