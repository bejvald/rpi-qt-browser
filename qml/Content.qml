/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0

Rectangle {
    id: root
    color: "transparent"

    property real volume: 0.5
    property bool autoStart: true
    property bool started: false


    Loader {
        id: contentLoader
        width: parent.width
        height: parent.height
    }


    onWidthChanged: {
        if (contentItem())
            contentItem().width = width
    }

    onHeightChanged: {
        if (contentItem())
            contentItem().height = height
    }


    function initVideo(path){
        console.log("[qml-browser] Content.initVideo \"" + path + "\"")
        stop()
        contentLoader.source = "ContentVideo.qml"
        contentLoader.item.mediaSource = path
        contentLoader.item.volume = volume
        if (root.autoStart){
            root.start()
            root.started = true
        }
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
    function updateRootSize() { root.height = contentItem().height }

}
