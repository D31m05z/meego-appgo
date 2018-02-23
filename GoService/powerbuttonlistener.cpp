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

#include "powerbuttonlistener.h"

PowerButtonListener::PowerButtonListener(QObject *parent) :
    QObject(parent)
{
    // signal sender=:1.3 -> dest=(null destination) serial=1125 path=/com/nokia/mce/request; interface=com.nokia.mce.request; member=powerkey_long_ind

    QDBusConnection::systemBus().connect("", "/com/nokia/mce/request", "com.nokia.mce.request", "powerkey_long_ind", this, SIGNAL(powerButtonLongPressed()));
    QDBusConnection::systemBus().connect("", "/com/nokia/mce/request", "com.nokia.mce.request", "powerkey_double_ind", this, SIGNAL(powerButtonDoubleClicked()));

    //PowerKeyDoubleAction=dbus-signal-powerkey_double_ind
}
