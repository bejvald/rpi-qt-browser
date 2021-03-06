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
import QtMultimedia 5.0

VideoOutput {
    source: mediaPlayer
    property alias mediaSource: mediaPlayer.source
    property alias volume: mediaPlayer.volume

    fillMode: VideoOutput.Stretch

    //Create the unique mediaplayer

    MediaPlayer {
        id: mediaPlayer
        autoPlay: true
        volume: parent.volume
        loops: Audio.Infinite
    }

    function play()  { mediaPlayer.play() }
    function pause() { mediaPlayer.pause() }
    function stop()  { mediaPlayer.stop() }

}
