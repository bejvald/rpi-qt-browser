/*
* Project: rpi-qt-browser
* Author: Björn Ejvald
* Date: 3.9.2013
*
* Copyright (c) 2013 Björn Ejvald. All rights reserved.
*
* This file is part of rpi-qt-browser.
*
* rpi-qt-browser is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* rpi-qt-browser is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with rpi-qt-browser. If not, see <http://www.gnu.org/licenses/>.
*/

#include "bridgeobject.h"
#include <QQuickItem>
#include <QMetaObject>

/*
 * Creates the object that is to be added to every site for access from javascript.
 * All methods can be accessed from javascript through objectName.function()
 *
 */
bridgeObject::bridgeObject(QQuickItem *parent) : QObject()
{
    root=parent;
}

/*
 * Return {String} the serial number
 */
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

/*
 * Return {String} the network interface MAC address
 */
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

/*
 * Return {String} the mode used for the display connected to the device,
 * for example "576p@50" or "1080i@60"
 */
QString bridgeObject::getDisplayMode()
{
    //Dummy function
    return QString("");
}

/*
 * Sets the mode used for the display connected to the device. The mode
 * specifies resolution, progressive or interlaced display and vertical
 * refresh interval.
 *
 * @param {String} displayMode the display mode as a string (e.g. "576p@50", "1080i@60")
 * @param {Integer} storageMode how to store the setting (0 for permanent, 1
 *     for volatile, defaults to permanent).
 */
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

/*
 * Return {Integer} the audio volume (as percentage of max volume)
 */
int bridgeObject::getVolume()
{
    float vol=root->property("targetVolume").toFloat();
    return int(vol*100);
}

/*
 * Sets the audio volume.
 *
 * @param {Integer} audio volume (as percentage of max volume)
 */
void bridgeObject::setVolume(int volume)
{
    float targetVolume=volume/100.0;
    root->setProperty("targetVolume", targetVolume);
    QMetaObject::invokeMethod(root, "setVolume");
}

/*
 * Return {Boolean} true if audio is muted, false otherwise, undefined if not known
 */
bool bridgeObject::isMuted()
{
    return root->property("muteStatus").toBool();
}

/*
 * Mute or unmute the system.
 *
 * @param {Boolean} muteEnabled if true, mute system, otherwise unmute system
 */
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

/*
 * Reboots the device.
 */
void bridgeObject::reboot()
{
    system("/sbin/reboot -f");
}

/*
 * Starts playback of a specified URI at speed 1. Can only be called when the media player
 * is currently closed.
 *
 * @param {String} uri the stream URI
 */
void bridgeObject::open(QString uri)
{
    QUrl fileName(uri);
    root->setProperty("fileName", fileName);
    QMetaObject::invokeMethod(root, "init");
}

/*
 * Plays the current stream at the specified speed. Supported speeds are 0 (paused), 1
 * (regular playback) and any trick play speeds supported for the current stream.
 *
 * @param speed the playback speed
 */
void bridgeObject::play(int speed)
{
    //Speed is not yet implemented in QML
    root->setProperty("playSpeed", speed);
    QMetaObject::invokeMethod(root, "play");
}

/*
 *Pauses the current stream.
 */
void bridgeObject::pause()
{
    QMetaObject::invokeMethod(root, "pause");
}

/*
 * Sets the position and dimensions of the video window in browser coordinates.
 * @param {Integer} x the x coordinate of the window
 * @param {Integer} y the y coordinate of the window
 * @param {Integer} width the width of the window
 * @param {Integer} height the height of the window
 */
void bridgeObject::setPosition(int x, int y, int width, int height)
{
    qDebug() << "bridge.setPosition";
    root->setProperty("tX", x);
    root->setProperty("tY", y);
    root->setProperty("tWidth", width);
    root->setProperty("tHeight", height);
    QMetaObject::invokeMethod(root, "setTargetPosition");
}

/*
 * Sets the position and size of the window to cover the entire screen.
 */
void bridgeObject::setFullscreen()
{
    qDebug() << "bridge.setFullScreen";
    root->setProperty("tX", 0);
    root->setProperty("tY", 0);
    root->setProperty("tWidth", root->width());
    root->setProperty("tHeight", root->height());
    QMetaObject::invokeMethod(root, "setTargetPosition");
}


