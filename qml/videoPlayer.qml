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

    Keys.onPressed: {
        if (event.key === Qt.Key_P){
            console.log("[qml-browser] main.keyPressed P")
        }
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
