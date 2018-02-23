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

#include "goservice.h"

GoService::GoService(QObject *parent)
    : QObject(parent)
{
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("/opt/AppGo/base/login.wav"));
    playlist->addMedia(QUrl::fromLocalFile("/opt/AppGo/base/beep.wav"));
    playlist->addMedia(QUrl::fromLocalFile("/opt/AppGo/base/wrong.wav"));
    playlist->addMedia(QUrl::fromLocalFile("/opt/AppGo/base/start.wav"));

    playlist->setCurrentIndex(LOGIN);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->setVolume(100);

    orientation = new Orientation(parent);
    orientation->setActive(false);

    connect(orientation, SIGNAL(orientationChanged(int)), SLOT(onChangeOrientationChange(int)));

    binaryTree = new BinaryTree();
    loadConfig();

    PowerButtonListener* listener = new PowerButtonListener(this);
    QObject::connect(listener, SIGNAL(powerButtonDoubleClicked()), this, SLOT(powerBtnDoubleClick()));

    timer = new QTimer(this);
    timer->setInterval(2000);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(startApp()));

    killerTimer = new QTimer(this);
    killerTimer->setInterval(8000);
    killerTimer->setSingleShot(true);
    connect(killerTimer, SIGNAL(timeout()), this, SLOT(timeOut()));

    rumble = new QFeedbackHapticsEffect();
    rumble->setAttackIntensity(0.0);
    rumble->setAttackTime(100);
    rumble->setFadeTime(100);
    rumble->setFadeIntensity(0.+0);
}

GoService::~GoService()
{
    delete orientation;
    delete binaryTree;
    delete playlist;
    delete player;
    delete timer;
    delete rumble;
}

void GoService::activate()
{
    /*
    MNotification notification(MNotification::DeviceEvent, "", QObject::tr("AppGo! show the start command..."));
    notification.setImage("icon-m-user-guide");
    notification.publish();
    */

    orientation->setActive(true);
    vibrate(1000, 0.4f);
    killerTimer->start();
}

QString rstrip(const QString& str)
{
    int n = str.size() - 1;
    for (; n >= 0; --n) {
        if (!str.at(n).isSpace()) {
            return str.left(n + 1);
        }
    }
    return "";
}

void GoService::loadConfig()
{
    QFile file("/home/user/appgo.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ERROR: open file";
        return;
    }

    int index = 0;
    while (!file.atEnd()) {
        QString line(file.readLine());
        line = rstrip(line);

        index++;
        if(index==1) {
            qDebug() << line;
        } else if(index==2) {
            QStringList codes = line.split(" ");
            for (int i = -1; i < codes.size(); ++i) {
                if(i==-1)
                    binaryTree->AddItem(0,false);
                else {
                    if(codes[i].toInt() != 0)
                        binaryTree->AddItem(codes[i].toInt(),true);
                }
            }
        } else if (index == 3 ) {
            binaryTree->AddItem(line);
            index=0;
        }
    }

    binaryTree->PrintTree();
}

void GoService::vibrate(int duration, qreal intensity)
{
    rumble->setIntensity(intensity);
    rumble->setDuration(duration);
    rumble->start();
}

void GoService::startApp()
{
    binaryTree->execute();
    orientation->setActive(false);
}

void GoService::timeOut()
{
    MNotification notification(MNotification::DeviceEvent, "", QObject::tr("timeout"));
    notification.setImage("icon-m-user-guide");
    notification.publish();

    orientation->setActive(false);
    playlist->setCurrentIndex(WRONG);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    player->play();
}

void GoService::onChangeOrientationChange(int state)
{
    qDebug() << "orientation:"<<state;

    if(killerTimer->isActive()) {
        killerTimer->stop();
        killerTimer->start();
    }

    if(timer->isActive()) {
        timer->stop();
    }

    if(binaryTree->FindCommand(state)) {
        qDebug() << "PASS";
        playlist->setCurrentIndex(PASS);
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();

        if(binaryTree->canExecute()) {
            playlist->setCurrentIndex(START);
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
            player->play();

            killerTimer->stop();
            timer->start();
        }
    } else {
        qDebug() << "WRONG";
        /*
        MNotification notification(MNotification::DeviceEvent, "", QObject::tr("unknown command"));
        notification.setImage("icon-m-user-guide");
        notification.publish();
        */

        killerTimer->stop();
        orientation->setActive(false);
        playlist->setCurrentIndex(WRONG);
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->play();
    }
}

void GoService::powerBtnDoubleClick()
{
    qDebug() << "powerBtn double click" << endl;

    playlist->setCurrentIndex(LOGIN);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    player->play();
    binaryTree->FindCommand(0);
    activate();
}
