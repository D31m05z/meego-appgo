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

Orientation::Orientation(QObject *parent) :
    QObject(parent)
{
    root = parent;
    active = false;

    qDebug() << "Sarting sensores" << endl;

    m_sensor = new QOrientationSensor(this);
    connect(m_sensor, SIGNAL(readingChanged()), SLOT(onReadingChanged()));
    m_sensor->start();

    //start position
    root->setProperty("actualStateImg","qrc:/images/FRONT_SIDE.png");
    root->setProperty("actualState","Front side");
}

Orientation::~Orientation() {
    delete m_sensor;
}

void Orientation::setActive(bool enable){
    active = enable;
}

void Orientation::vibrate(){

}

void Orientation::onReadingChanged()
{
    if(active){
        QOrientationReading* reading = m_sensor->reading();
        switch(reading->orientation())
        {
        case QOrientationReading::TopUp:
            root->setProperty("actualStateImg","qrc:/images/TOP_SIDE.png");
            root->setProperty("actualState","Top side");

            qDebug() << "TopUp:" << QOrientationReading::TopUp <<endl;
            vibrate();

            emit orientationChanged(1);
            break;
        case QOrientationReading::TopDown:
            root->setProperty("actualStateImg","qrc:/images/BOTTOM_SIDE.png");
            root->setProperty("actualState","Bottom side");
            qDebug() << "TopDown:" << QOrientationReading::TopDown << endl;
            vibrate();

            emit orientationChanged(2);
            break;
        case QOrientationReading::LeftUp:
            root->setProperty("actualStateImg","qrc:/images/LEFT_SIDE.png");
            root->setProperty("actualState","Left side");
            qDebug() << "LeftUp:" << QOrientationReading::LeftUp << endl;
            vibrate();

            emit orientationChanged(3);
            break;
        case QOrientationReading::RightUp:
            root->setProperty("actualStateImg","qrc:/images/RIGHT_SIDE.png");
            root->setProperty("actualState","Right side");
            qDebug() << "RightUp:" << QOrientationReading::RightUp << endl;
            vibrate();

            emit orientationChanged(4);
            break;
        case QOrientationReading::FaceDown:
            root->setProperty("actualStateImg","qrc:/images/BACK_SIDE.png");
            root->setProperty("actualState","Back side");
            qDebug() << "FaceDown" << endl;
            vibrate();

            emit orientationChanged(6);
            break;
        case QOrientationReading::FaceUp:
            root->setProperty("actualStateImg","qrc:/images/FRONT_SIDE.png");
            root->setProperty("actualState","Front side");
            qDebug() << "FaceUp:" << QOrientationReading::FaceUp << endl;
            vibrate();

            emit orientationChanged(5);
            break;
        default:
            break;
        }
    }
}
