import QtQuick 2.0

Rectangle {
    id: root
    color: "transparent"

    property string fileName
    property int targetX
    property int targetY
    property int targetWidth
    property int targetHeight
    property real targetVolume
    property bool muteStatus
    property int playSpeed

    Content {
        id: content
        x: 0
        y: 0
        width: 1280
        height: 720
        state: "left"

        states: [
            State {
                name: "fullScreen"
                PropertyChanges { target: content; x:  parent.x  }
                PropertyChanges { target: content; y:  parent.y  }
                PropertyChanges { target: content; width:  parent.width  }
                PropertyChanges { target: content; height: parent.height }
            }
        ]

        transitions: [
            Transition {
                ParallelAnimation {
                    PropertyAnimation {
                        property: "width"
                        easing.type: Easing.Linear
                        duration: 250
                    }
                    PropertyAnimation {
                        property: "height"
                        easing.type: Easing.Linear
                        duration: 250
                    }
                    PropertyAnimation {
                        property: "x"
                        easing.type: Easing.Linear
                        duration: 250
                    }
                    PropertyAnimation {
                        property: "y"
                        easing.type: Easing.Linear
                        duration: 250
                    }
                }
            }
        ]
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
    function toggleFullScreen(){
        if (content.state != "fullScreen"){
            console.log("[qml-browser] changed to fullScreen");
            content.state="fullScreen";
        }
        else{
            console.log("[qml-browser] changed to baseState");
            content.state="baseState";
        }
    }


    //Hibox API-functions for the MediaPlayer:

    function getVolume(){
        return content.volume
    }
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
        content.x=targetX;
        content.y=targetY;
        content.height=targetHeight;
        content.width=targetWidth;
    }
    function setFullscreen(){
        content.state="fullScreen";
    }
}
