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

#include <QtGui/QApplication>
#include <QtDeclarative>
#include <QSplashScreen>
#include <QDebug>

#include "qmlapplicationviewer.h"
#include "gosystem.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    qDebug() << "entering..." << endl;
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    qDebug() << "$pSplash" << endl;
    QSplashScreen *pSplash = new QSplashScreen();
    pSplash->setPixmap(QPixmap("/opt/AppGo/base/splash.png"));
    pSplash->show();

    qDebug() << "$viewer" << endl;
    QDeclarativeView viewer;
    viewer.setSource(QUrl("qrc:/qml/main.qml"));

    qDebug() << "$security" << endl;
    GoSystem goSystem(dynamic_cast<QObject*>(viewer.rootObject()));

    viewer.rootContext()->setContextProperty("myGo", &goSystem);
    viewer.showFullScreen();

    qDebug() << "$inicialize" << endl;
    qDebug() << "$pSplash close" << endl;
    pSplash->close();
    delete pSplash;

    return app->exec();
}

