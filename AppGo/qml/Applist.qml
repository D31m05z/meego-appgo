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


Item {

    property real oldX: 0
    property real oldY: 0
    property real changeX: 0
    property bool edit: false
    property bool share: false
    property bool mousePressed: false

    property int errorCount: 0
    Component {
        id: applistDelegate

        Item {
            height: 85
            width: listview.width
            x: index == app.index ? -changeX/2 : 0
            opacity:  ((index == app.index) ? 1 : 15/Math.abs(changeX))

            Rectangle{
                anchors.fill: parent
                // color: ( (index == app.index) ? ((edit==true || share==true) ? "red":"#eeebeb") : (selected ? "green":"gray") )
                color: selected? "#11b9c8" : ( index == app.index ? ( edit? "red" : "gray" ) :"white" )
                opacity: 0.2
            }

            Image {
                id: appIcon
                source:  "file:"+icon
                width: 80
                height: 80

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 0
                anchors.leftMargin: 20

                onStatusChanged:{

                    if (appIcon.status == Image.Ready){
                        errorCount = 0;
                        console.log("Loaded")
                    }

                    if (appIcon.status == Image.Error){
                        errorCount++;

                        //console.log("error image load:" + icon);
                        console.log(appIcon.source)
                        if(errorCount == 1){
                            appIcon.source = "file:/usr/share/themes/blanco/meegotouch/icons/"+icon+".png"
                        } else if(errorCount == 2){
                            appIcon.source = "file:/opt/AppGo/base/fuck.png";
                        }
                    }

                }
            }

            Text {
                id: appName
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 20
                anchors.leftMargin: 120

                width: parent.width
                font.pixelSize:  index == app.index ? 33 : 30
                font.family: "Chaparral Pro Light"
                color: "white"
                //selected? "green" : index == app.index ? "black" : "#2e2f2e"
                text: name
            }


            MouseArea {
                id:mouseEvent
                anchors.fill: parent

                onPressed: {
                    console.log("onPressed");
                    oldX = mouseX;
                    oldY = mouseY;
                    mousePressed = true;
                }

                onMouseXChanged: {
                    if(mousePressed){
                        app.index = index;
                        changeX =  oldX-mouseX;

                        if(changeX>=10){
                            share = true;
                            if(background.state != "remove")
                                background.state = "remove"

                        } else if(changeX<=-10){
                            edit = true;

                            if(background.state != "settings")
                                background.state = "settings"
                        }

                        if(changeX>=100) {
                            console.log("share");
                            console.log(index);

                            selectd = name;

                            if(myGo.haveCommand(selectd))
                                app.applistModel.setProperty(index, "selected", !selected);

                            if(selected){
                                console.log("SELECTED");
                            }else{
                                console.log("NOT SELECTED");
                                myGo.removeCommand(selectd);
                            }

                            mousePressed = false;
                            edit = false;
                            share = false;
                            changeX = 0;
                            background.state = "back"
                        }
                        else if(changeX<=-100){
                            console.log("edit");
                            myGo.orientationEnable(true);
                            myGo.setSelectedItem(name);
                            selectd = name;

                            selectdIcon = appIcon.source;
                            selectdIndex = index;
                            pageStack.push(settingAccount);

                            mousePressed = false;
                            edit = false;
                            share = false;
                            changeX = 0;
                            background.state = "back"
                        }
                    }
                }

                onDoubleClicked: {
                    console.log("onDoubleClicked");
                }

                onPressAndHold: {
                    console.log("onPressAndHold");
                }

                onClicked: {
                    console.log("onClicked");
                }

                onReleased: {
                    console.log("onReleased");
                    edit = false;
                    share = false;
                    changeX = 0;
                    background.state = "back"
                }
            }

            Behavior on x {
                SpringAnimation {
                    spring: 2
                    damping: 0.2
                }
            }
        }
    }

    ListView {
        id: listview

        anchors.fill: parent
        model: app.applistModel
        delegate: applistDelegate
        currentIndex: app.index
        cacheBuffer: height
        clip: true
        highlightMoveDuration: 500
        spacing: 5

        ScrollDecorator {
            flickableItem: parent
        }

        onContentYChanged: {
            //console.log("onContentYChanged");
            edit = false;
            share = false;
            changeX = 0;
            background.state = "back"
        }
    }
}
