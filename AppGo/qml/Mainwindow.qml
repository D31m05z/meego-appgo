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
import "Storage.js" as Storage

Page {
    id: mainwindow
    objectName: "mainwindow"

    orientationLock:  PageOrientation.LockPortrait

    function addNewIcon(exec,name,icon,active){
        //  console.log("addNewIcon");
        app.addIcon(exec,name,icon,active)
    }

    FontLoader { id: iFont; source: "../fonts/AgencyFB.ttf" }

    App {
        id: app

        Component.onCompleted: {

            console.log("onCompleted | LOAD SETTINGS");

            Storage.initialize()

            Storage.getApplist(applist)

            var res = Storage.getSetting("volume")
            if (res != "Unknown")
                volume = parseFloat(res)

            res = Storage.getSetting("index")
            if (res != "Unknown") {
                index = parseInt(res)
            }

            res = Storage.getSetting("encoding")
            if (res != "Unknown") {

            }
            res = Storage.getSetting("sample_rate")
            if (res != "Unknown") {

            }
            res = Storage.getSetting("bitrate")
            if (res != "Unknown") {

            }

            res = Storage.getSetting("advancedUse")
            if (res != "Unknown") {

            }
            res = Storage.getSetting("container")
            if (res != "Unknown") {

            }
            res = Storage.getSetting("saveFolder")
            if (res != "Unknown") {

            }
            res = Storage.getSetting("cdQuality")
            if (res != "Unknown") {

            }

            console.log("onCompleted | LOADED");
        }

        Component.onDestruction: {
            console.log("onDestruction | SAVE SETTINGS");
            //    myGo.exitAndActivating();
            console.log("onDestruction | SAVED");
        }

    }

    ///////////////////////////////////////////////////

    PageStack {
        id: pageStack
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Image {
            id: black
            anchors.fill: parent
            source: "../images/black.png"
        }

        MainPage{
            id: imainPage
        }

        AppListPage {
            id: appPage
        }

        AboutPage {
            id: aboutPage
            backgroundImage: "../images/background-about.png"
        }

        SettingsAccount {
            id: settingAccount
            backgroundImage: "../images/background-back.png"
        }

        Powersave {
            id: suspend
        }
    }

    Component.onCompleted: {
        pageStack.push(imainPage);
    }

    Component.onDestruction: {
        console.log("--DESTRUCTOR");

        if(myGo.isPassRecording())
            myGo.stopPasswordRecord();

        myGo.beforeExit();
    }

    function powerSaveON(){
        if(pageStack.currentPage!=suspend){
            pageStack.push(suspend);
            console.log("=====SUSPEND-SWITCH-==ON=======");
        }
    }

    function powerSaveOFF(){
        if(pageStack.currentPage!=imainPage){
            pageStack.push(imainPage);
            console.log("=====SUSPEND-SWITCH-==OFF======");
        }
    }

    states: [
        State {
            name: "fullsize-visible"
            when: platformWindow.viewMode == WindowState.Fullsize && platformWindow.visible
            StateChangeScript {
                script: {
                    powerSaveOFF();
                }
            }
        },
        State {
            name: "thumbnail-or-invisible"
            when: platformWindow.viewMode == WindowState.Thumbnail
            StateChangeScript {
                script: {
                    powerSaveON();
                }
            }
        }
    ]
}
