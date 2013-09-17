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

import QtQuick 2.0

Rectangle {
    id: root
    color: "transparent"

    property string fileName
    property int tX
    property int tY
    property int tWidth
    property int tHeight
    property real targetVolume
    property bool muteStatus
    property int playSpeed

    Content {
        id: content
        x: 0
        y: 0
        width: 1280
        height: 720
    }

    function init() {
        console.log("[videoPlayer] main.init")
        if (fileName != "")
        {
            content.initVideo(fileName)
        }
    }
    function setSource(source){
        fileName=source
    }

    //Hibox API-functions for the MediaPlayer:

    function setVolume(){
        content.volume=targetVolume;
    }
    function mute(){
        Content.mute(muteStatus);
    }
    function play(){
        content.play();
    }
    function pause(){
        content.pause();
    }
    function setTargetPosition(){
        console.log("videoPlayer.setTargetPosition: "
                    + tX + " " + tY + " " + tHeight + " " + tWidth);
        content.x=tX;
        content.y=tY;
        content.height=tHeight;
        content.width=tWidth;
    }
}
