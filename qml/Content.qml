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

    property real volume: 0.5
    property bool autoStart: true
    property bool started: false
    property bool initiated: false


    Loader {
        id: contentLoader
        width: parent.width
        height: parent.height
    }

    function initVideo(path){
        console.log("[qml-browser] Content.initVideo \"" + path + "\"")
        if(!initiated){
            stop()
            contentLoader.source = "ContentVideo.qml"
            contentLoader.item.mediaSource = path
            contentLoader.item.volume = volume
            if (root.autoStart){
                root.start()
                root.started = true
            }
            initiated=true;
        }
        play();
    }

    function openVideo(path) {
        console.log("[qml-browser] Content.openVideo \"" + path + "\"")
        stop()
        contentLoader.source = "ContentVideo.qml"
        contentLoader.item.mediaSource = path
        contentLoader.item.volume = volume
        contentLoader.item.play()
        root.started = true
    }

    function stop() {
        console.log("[qml-browser] Content.stop")
        if (contentLoader.item) {
            contentLoader.item.stop()
            root.started = false
        }
    }

    function start() {
        console.log("[qml-browser] Content.start")
        if (contentLoader.item) {
            if (contentLoader.source == "ContentVideo.qml"){
                contentLoader.item.play()
                root.started = true
            }
        }
    }
    function play() {
        console.log("[qml-browser] Content.play")
        if (contentLoader.item) {
            contentLoader.item.play()
            root.started = true
        }
    }

    function pause() {
        console.log("[qml-browser] Content.pause")
        if (contentLoader.item) {
            contentLoader.item.pause()
            root.started = false
        }
    }

    function mute(value) {
        console.log("[qml-browser] Content.mute: " + value)
        if (contentLoader.item) {
            contentLoader.item.muted=value;
        }
    }

    function contentItem() { return contentLoader.item }

}
