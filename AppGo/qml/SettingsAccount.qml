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

Page {
    id: accountID
    opacity: 0

    orientationLock:  PageOrientation.LockPortrait

    clip: true

    property alias backgroundImage:  background.source

    FontLoader { id: iFont; source: "../fonts/AgencyFB.ttf" }

    Image {
        id: background
        anchors.fill: parent
        z: -1

        //----------------swipe---------------------------------
        MouseArea {
            anchors.fill: background
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
                    if( oldX < mouseX) {
                        if(settingAccount.status == PageStatus.Active){
                            console.log("imainPage");
                            if(isPassRecording)
                                myGo.stopPasswordRecord();

                            if(myGo.haveCommand(selectd))
                                app.applistModel.setProperty(selectdIndex, "selected", true);

                            myGo.orientationEnable(false);
                            pageStack.pop(appPage);
                        }
                    }
                }

                if(mouseY<115 && mouseX<150){
                    if(settingAccount.status == PageStatus.Active){
                        console.log("imainPage");
                        if(isPassRecording)
                            myGo.stopPasswordRecord();

                        if(myGo.haveCommand(selectd))
                            app.applistModel.setProperty(selectdIndex, "selected", true);

                        myGo.orientationEnable(false);
                        pageStack.pop(appPage);
                    }
                }
            }
        }
        //----------------swipe---------------------------------
    }

    Image{
        id: settings_items
        x:50
        y:200
        source: actualStateImg
    }

    Button {
        id: recordPassword;
        x:70
        y:500
        text: isPassRecording ? "finish" : "record your command";
        font.family: iFont.name

        onClicked: {
            if(isPassRecording){
                myGo.stopPasswordRecord();

                if(myGo.haveCommand(selectd))
                    app.applistModel.setProperty(selectdIndex, "selected", true);
            }
            else{
                myGo.startPasswordRecord();
            }

        }
    }

    Text {
        x:5
        y:100

        font.family: iFont.name
        font.pixelSize: 40
        text: password
        color: "white"
    }

    Image {
        id: appIcon
        source:  "file:"+selectdIcon
        width: 80
        height: 80

        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 100;
        anchors.horizontalCenterOffset: 0;
        anchors.horizontalCenter: parent.horizontalCenter;
    }

    Text {  font.pointSize: 40; text: selectd; anchors.bottom: parent.bottom; anchors.bottomMargin: 40; anchors.horizontalCenterOffset: 0; font.bold: true; verticalAlignment: Text.AlignTop; horizontalAlignment: Text.AlignHCenter; anchors.horizontalCenter: parent.horizontalCenter; font.family: iFont.name; color:"white"}
    Text {  font.pointSize: 20; text: "developer: Gergely Boross | aFagylaltos(c)"; anchors.bottom: parent.bottom; anchors.bottomMargin: 20; anchors.horizontalCenterOffset: 0; font.bold: false; verticalAlignment: Text.AlignTop; horizontalAlignment: Text.AlignHCenter; anchors.horizontalCenter: parent.horizontalCenter; font.family: iFont.name; color:"white"}

    states: [
        State {
            name: "begin"
            when: accountID.visible
            PropertyChanges {
                target: accountID
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
