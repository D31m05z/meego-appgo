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
*       This : is a part of the work done by aFagylaltos.     *
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

#include <QOrientationSensor>
#include <QDebug>

#include "orientation.h"

Orientation::Orientation(QObject *parent)
    : QObject(parent)
{
    active = false;
    qDebug() << "Sarting sensores" << endl;

    m_sensor = new QOrientationSensor(this);
    m_sensor->setActive(true);
    m_sensor->setProperty("alwaysOn",true);

    connect(m_sensor, SIGNAL(readingChanged()), SLOT(onReadingChanged()));
    m_sensor->start();

    //qDebug() << "rezeg" <<endl;
    //vibrate();
}

Orientation::~Orientation()
{
    delete m_sensor;
    //  qDebug() << "rumble elott" << endl;
    //delete rumble;
    //qDebug() << "rumble utan" << endl;
}

void Orientation::setActive(bool enable)
{
    qDebug() << "SENSORE_ACTIV? >" << enable;
    active = enable;
}

void Orientation::vibrate()
{

}

void Orientation::onReadingChanged()
{
    if(!active) return;

    QOrientationReading* reading = m_sensor->reading();
    switch(reading->orientation())
    {
    case QOrientationReading::TopUp:
        //  qDebug() << "TopUp" << endl;
        vibrate();

        emit orientationChanged(QOrientationReading::TopUp);
        break;
    case QOrientationReading::TopDown:
        //  qDebug() << "TopDown" << endl;
        vibrate();

        emit orientationChanged(QOrientationReading::TopDown);
        break;
    case QOrientationReading::LeftUp:
        //  qDebug() << "LeftUp" << endl;
        vibrate();

        emit orientationChanged(QOrientationReading::LeftUp);
        break;
    case QOrientationReading::RightUp:
        //  qDebug() << "RightUp" << endl;
        vibrate();

        emit orientationChanged(QOrientationReading::RightUp);
        break;
    case QOrientationReading::FaceDown:
        //  qDebug() << "FaceDown" << endl;
        vibrate();

        emit orientationChanged(QOrientationReading::FaceDown);
        break;
    case QOrientationReading::FaceUp:
        //  qDebug() << "FaceUp" << endl;
        vibrate();
        // passwordActiv = true;
        // player->stop();

        emit orientationChanged(QOrientationReading::FaceUp);
        break;
    default:
        break;
    }
}
