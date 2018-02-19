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


function openDatabase() {
    return openDatabaseSync("appgoV4", "1.3", "Settings", 100000)
}

function initialize() {
    var db = openDatabase()
    db.transaction(
        function(tx) {
            tx.executeSql("CREATE TABLE IF NOT EXISTS settings(setting TEXT UNIQUE, value TEXT)")
            tx.executeSql("CREATE TABLE IF NOT EXISTS applist(exec TEXT, name TEXT, icon TEXT, selected BOOLEAN)")
        }
    )
}

function setSetting(setting, value) {
    var db = openDatabase()
    var res = "Error"
    db.transaction(
        function(tx) {
            var rs = tx.executeSql("INSERT OR REPLACE INTO settings VALUES (?,?);", [setting,value])
            if (rs.rowsAffected > 0)
                res = "OK"
        }
    )
    return res
}

function getSetting(setting) {
    var db = openDatabase()
    var res = "Unknown"
    db.transaction(
        function(tx) {
            var rs = tx.executeSql("SELECT value FROM settings WHERE setting=?;", [setting])
            if (rs.rows.length > 0)
                res = rs.rows.item(0).value
        }
    )
    return res
}

function getApplist(applist) {
    var db = openDatabase()
    var res = "Unknown"
    db.transaction(
        function(tx) {
            var rs = tx.executeSql("SELECT * FROM applist;")
            if (rs.rows.length > 0) {
                for (var i = 0; i < rs.rows.length; i++) {
                    applist.append({"exec": rs.rows.item(i).exec, "name": rs.rows.item(i).name, "icon": rs.rows.item(i).icon, "selected": rs.rows.item(i).selected})
                }
                res = "OK"
            }
        }
    )
    return res
}

function setApplist(applist) {
    var db = openDatabase()
    var res = "Error"
    db.transaction(
        function(tx) {
            var rs = tx.executeSql("DELETE FROM applist;")
            var count = 0
            for (var i = 0; i < applist.count; i++) {
                rs = tx.executeSql("INSERT OR REPLACE INTO applist VALUES (?,?,?,?);", [applist.get(i).exec, applist.get(i).name, applist.get(i).icon,applist.get(i).selected])
                count += rs.rowsAffected
            }

            if (count > 0)
                res = "OK"
        }
    )
    return res
}
