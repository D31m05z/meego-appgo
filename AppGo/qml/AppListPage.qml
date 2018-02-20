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
    id: appListPage
    opacity: 0
    orientationLock:  PageOrientation.LockPortrait

    Image {
        id: settings
        anchors.fill: parent
        z: -1
        opacity: 0
        source: "../images/background-settings.png"
    }

    Image {
        id: remove
        anchors.fill: parent
        z: -1
        opacity: 0
        source: "../images/background-remove.png"
    }

    Image {
        id: background
        source:  "../images/background-back.png"
        anchors.fill: parent

        states: [
            State {
                name: "settings"
                PropertyChanges {
                    target: settings
                    opacity: 1
                }
                PropertyChanges {
                    target: background
                    opacity: 0
                }
            },
            State {
                name: "remove"
                PropertyChanges {
                    target: remove
                    opacity: 1
                }
                PropertyChanges {
                    target: background
                    opacity: 0
                }
            },
            State {
                name: "back"
                PropertyChanges {
                    target: background
                    opacity: 1
                }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "opacity"; duration: 300 }
        }
    }

    //----------------swipe--------------------------------
    MouseArea {
        id: mouseArea
        anchors.fill: background;

        property int oldX: 0
        property int oldY: 0

        onPressed: {
            oldX = mouseX;
            oldY = mouseY;
        }

        onReleased: {
            var xDiff = oldX - mouseX;
            var yDiff = oldY - mouseY;
            if( Math.abs(xDiff) > Math.abs(yDiff) ) {
                if( oldX > mouseX) {
                    if(appPage.status == PageStatus.Active){
                        console.log("controlPage");
                        //pageStack.push(controlPage);
                    }
                } else {
                    if(appPage.status == PageStatus.Active){
                        console.log("main");
                        pageStack.push(imainPage);
                    }
                }
            }

            if( (mouseX>340 && mouseX<480) && (mouseY<114)){
                if(appPage.status == PageStatus.Active){
                    console.log("controlPage");
                    //pageStack.push(controlPage);
                }
            }else if( (mouseX>0 && mouseX<120) && ( mouseY<114)){
                if(appPage.status == PageStatus.Active){
                    console.log("main");
                    pageStack.push(imainPage);
                }
            }
        }
    }
    //----------------swipe---------------------------------

    Applist {
        id: applist

        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 110
        anchors.bottomMargin: 0
        anchors.fill: parent
    }

    states: [
        State {
            name: "begin"
            when: appListPage.visible
            PropertyChanges {
                target: appListPage
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
}
