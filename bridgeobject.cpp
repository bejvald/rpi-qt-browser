#include "bridgeobject.h"
#include <QQuickItem>
#include <QMetaObject>

bridgeObject::bridgeObject(QQuickItem *parent) : QObject()
{
    root=parent;
}
//Hibox API

QString bridgeObject::getSerialNumber()
{
    QString serial;
    QFile file("/proc/cpuinfo");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Could not open file for reading";
        serial=QString("Error: File could not open");
        return serial;
    }
    QTextStream in(&file);
    for (int i=0; i<12; i++)
    {
        QString line = in.readLine();
        QStringList wordLine = line.split(":");

        if(line.contains("Serial"))
        {
            serial=wordLine.at(1);
            serial.replace(" ", "");
            qDebug() << "bridge.serial: " + serial;
            file.close();
        }
        else
        {
            serial=QString("File not found");
        }
    }
    file.close();
    return serial;
}

QString bridgeObject::getMacAddress()
{
    QString address;
    QFile file("/sys/class/net/eth0/address");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Could not open file for reading";
        address=QString("Error: Could not open file");
        return address;
    }

    QTextStream in(&file);
    address=in.readLine();
    qDebug() << "bridge.macaddress: " + address;
    return address;
}

QString bridgeObject::getDisplayMode()
{
    //Dummy function
    return QString("");
}

void bridgeObject::setDisplayMode(QString displaymode, int storagemode)
{
    //Dummy function
}

QString bridgeObject::getFirstAudioLanguage()
{
    //Dummy function
    return QString("");
}

void bridgeObject::setFirstAudioLanguage(QString lang, int storagemode)
{
    //Dummy function
}

QString bridgeObject::getSecondAudioLanguage()
{
    //Dummy function
    return QString("");
}

void bridgeObject::setSecondAudioLanguage(QString lang, int storagemode)
{
    //Dummy function
}

QString bridgeObject::getFirstSubtitleLanguage()
{
    //Dummy function
    return QString("");
}

void bridgeObject::setFirstSubtitleLanguage(QString lang, int storagemode)
{
    //Dummy function
}

QString bridgeObject::getSecondSubtitleLanguage()
{
    //Dummy function
    return QString("");
}

void bridgeObject::setSecondSubtitleLanguage(QString lang, int storagemode)
{
    //Dummy function
}

int bridgeObject::getVolume()
{
    float vol=root->property("targetVolume").toFloat();
    return int(vol*100);
}

void bridgeObject::setVolume(int volume)
{
    float targetVolume=volume/100.0;
    root->setProperty("targetVolume", targetVolume);
    QMetaObject::invokeMethod(root, "setVolume");
}

bool bridgeObject::isMuted()
{
    return root->property("muteStatus").toBool();
}

void bridgeObject::mute(bool muteStatus)
{
    root->setProperty("muteStatus", muteStatus);
    QMetaObject::invokeMethod(root, "mute");
}

QString bridgeObject::getStandbyState()
{
    //Dummy function
    return QString("");
}

void bridgeObject::setStandbyState(bool standby)
{
    //Dummy function
}

void bridgeObject::reboot()
{
    system("/sbin/reboot -f");
}

void bridgeObject::open(QString uri)
{
    QUrl fileName(uri);
    root->setProperty("fileName", fileName);
    QMetaObject::invokeMethod(root, "init");
}

void bridgeObject::play(int speed)
{
    //Dummy function, not implemented in QML
    root->setProperty("playSpeed", speed);
    QMetaObject::invokeMethod(root, "play");
}

void bridgeObject::pause()
{
    QMetaObject::invokeMethod(root, "pause");
}

void bridgeObject::setPosition(int x, int y, int width, int height)
{
    root->setProperty("targetX", x);
    root->setProperty("targetY", y);
    root->setProperty("targetWidth", width);
    root->setProperty("targetHeight", height);
    QMetaObject::invokeMethod(root, "setTargetPosition");
}

void bridgeObject::setFullscreen()
{
    root->setProperty("targetX", 0);
    root->setProperty("targetY", 0);
    root->setProperty("targetWidth", root->width());
    root->setProperty("targetHeight", root->height());
    QMetaObject::invokeMethod(root, "setTargetPosition");
}


