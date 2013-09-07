#include "bridgeobject.h"
#include <QQuickItem>
#include <QMetaObject>

bridgeObject::bridgeObject(QQuickItem *parent) : QObject()
{
    root=parent;
}
//Hibox API

int bridgeObject::getVolume(){
    //TODO: Implement this
    return 0;
}
void bridgeObject::setVolume(int volume){
    float targetVolume=volume/100.0;
    root->setProperty("targetVolume", targetVolume);
    QMetaObject::invokeMethod(root, "setVolume");
}

void bridgeObject::open(QString uri){
    QUrl fileName(uri);
    root->setProperty("fileName", fileName);
    QMetaObject::invokeMethod(root, "play");
}

void bridgeObject::play(int speed){
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


