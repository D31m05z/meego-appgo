/** * * * Gergely Boross - 2012_02_27 * * * * * * * * * * * * *\
*    _ _____   _____        __ _                              *
*   (_)  __ \ / ____|      / _| |                             *
*   |_| |__)| (___    ___ | |_| |___      ____ _ _ __ ___     *
*   | |  _  / \___ \ / _ \|  _| __\ \ /\ / / _` | '__/ _ \    *
*   | | | \ \ ____) | (_) | | | |_ \ V  V / (_| | | |  __/    *
*   |_|_|  \_\_____/ \___/|_|  \__| \_/\_/ \__,_|_|  \___|    *
*                                                             *
*                http://irsoftware.net                        *
*                                                             *
*              contact_adress: sk8Geri@gmail.com               *
*                                                               *
*       This file is a part of the work done by aFagylaltos.     *
*         You are free to use the code in any way you like,      *
*         modified, unmodified or copied into your own work.     *
*        However, I would like you to consider the following:    *
*                                                               *
*  -If you use this file and its contents unmodified,         *
*              or use a major part of this file,               *
*     please credit the author and leave this note untouched.   *
*  -If you want to use anything in this file commercially,      *
*                please request my approval.                    *
*                                                              *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

import QtQuick 1.1
import com.nokia.meego 1.0
import com.meego.extras 1.0

Page {
    id: irMAIN
    orientationLock:  PageOrientation.LockPortrait

    clip: true

    x: -changeX/2

    property real oldX: 0
    property real oldY: 0
    property real changeX: 0
    property bool mousePressed: false

    Image {
        id: swipe_settings
        anchors.fill: parent
        z: -1
        opacity: 0
        source: "../images/background-settings-swipe.png"
    }

    Image {
        id: swipe_about
        anchors.fill: parent
        z: -1
        opacity: 0
        source: "../images/background-about-swipe.png"
    }

    Image {
        id: backGround
        source:  "../images/background.png"
        anchors.fill: parent
        z:-1
        opacity:  15/Math.abs(changeX)

        //----------------swipe---------------------------------
        MouseArea {
            anchors.fill: backGround
            onPressed: {
                oldX = mouseX;
                oldY = mouseY;

                if(mouseY>115){
                    mousePressed = true;
                }
            }

            onReleased: {
                var xDiff = oldX - mouseX;
                var yDiff = oldY - mouseY;
                if( !mousePressed && (Math.abs(xDiff) > Math.abs(yDiff)) ) {
                    if( oldX > mouseX) {
                        if(imainPage.status == PageStatus.Active){
                            console.log("appPage");
                            pageStack.push(appPage);
                            mousePressed = false;
                            changeX = 0;
                        }
                    } else {
                        if(imainPage.status == PageStatus.Active){
                            console.log("aboutPage");
                            pageStack.push(aboutPage);
                            mousePressed = false;
                            changeX = 0;
                        }
                    }
                }

                if( (mouseX>340 && mouseX<480) && (mouseY<115)){
                    if(imainPage.status == PageStatus.Active){
                        console.log("appPage");
                        pageStack.push(appPage);
                        mousePressed = false;
                        changeX = 0;
                    }
                }else if( (mouseX>0 && mouseX<120) && (mouseY<115)){
                    if(imainPage.status == PageStatus.Active){
                        console.log("aboutPage");
                        pageStack.push(aboutPage);
                        mousePressed = false;
                        changeX = 0;
                    }
                }

                mousePressed = false;
                changeX = 0;
                backGround.state = "back"
            }

            onMouseXChanged: {
                if(mousePressed){
                    changeX =  oldX-mouseX;

                    if(changeX>=10){
                        if(backGround.state != "about")
                            backGround.state = "about"

                    } else if(changeX<=-10){
                        if(backGround.state != "list")
                            backGround.state = "list"
                    }

                    if(changeX>=200) {
                        console.log("aboutPage");
                        pageStack.push(aboutPage);

                        mousePressed = false;
                        changeX = 0;
                        backGround.state = "back"
                    }
                    else if(changeX<=-200){
                        console.log("appPage");
                        pageStack.push(appPage);

                        mousePressed = false;
                        changeX = 0;
                        backGround.state = "back"
                    }
                }
            }
        }

        states: [
            State {
                name: "list"
                PropertyChanges {
                    target: swipe_settings
                    opacity: 1
                }
                PropertyChanges {
                    target: backGround
                    opacity: 0
                }
            },
            State {
                name: "about"
                PropertyChanges {
                    target: swipe_about
                    opacity: 1
                }
                PropertyChanges {
                    target: backGround
                    opacity: 0
                }
            },
            State {
                name: "back"
                PropertyChanges {
                    target: backGround
                    opacity: 1
                }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "opacity"; duration: 300 }
        }

    }

    Image {
        id: state
        opacity:  1/Math.abs(changeX)
        source:  activated ? "../images/activated.png" : "../images/inactivated.png"
        x: 140
        y: 150
        MouseArea{
            id: state_change
            anchors.fill: parent
            onClicked:{

                if(!activated)
                    myGo.exitAndActivating();

                activated = true;
            }
        }
    }

    Column {
        opacity:  1/Math.abs(changeX)
        x:30
        y:350

        Text {
            font.pointSize: 30
            font.family: iFont.name
            textFormat: TextEdit.PlainText
            text: "==========\nInstructions\n=========="
            color:"white"
            font.bold: true
        }
        Text {
            font.pointSize: 18
            font.family: iFont.name
            textFormat: TextEdit.PlainText
            text: "1) Set up commands for your Apps"
            color:"white"
            width: 400
            wrapMode: Text.WordWrap
            font.bold: true
        }
        Text {
            font.pointSize: 18
            font.family: iFont.name
            textFormat: TextEdit.PlainText
            text: "2) Start the AppGo service by pushing the appropriate icon"
            color:"white"
            width: 400
            wrapMode: Text.WordWrap
            font.bold: true
        }
        Text {
            font.pointSize: 18
            font.family: iFont.name
            textFormat: TextEdit.RichText
            text: "3) Double press the power button and do the motion that you have already sat up before."
            color:"white"
            width: 400
            wrapMode: Text.WordWrap
            font.bold: true
        }
        Text {
            font.pointSize: 18
            font.family: iFont.name
            textFormat: TextEdit.RichText
            text: "4) And when you hear the double beep, your app will start."
            color:"white"
            width: 400
            wrapMode: Text.WordWrap
            font.bold: true
        }
    }

    states: [
        State {
            name: "begin"
            when: irMAIN.visible
            PropertyChanges {
                target: irMAIN
                opacity: 1
            }
        }
    ]

    transitions: [
        Transition {
            from: "*"
            to: "begin"
            PropertyAnimation { properties: "opacity"; duration: 800 }
        }
    ]

    Behavior on x {
        SpringAnimation {
            spring: 2
            damping: 0.2
        }
    }
}
