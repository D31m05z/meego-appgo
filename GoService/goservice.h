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

#ifndef GOSERVICE_H
#define GOSERVICE_H

#include <QObject>
#include <QFile>

#include <QMediaPlaylist>
#include <QMediaPlayer>

#include <MComponentData>
#include <MNotification>
#include <QTimer>

#include "orientation.h"
#include "binarytree.h"

#include "powerbuttonlistener.h"

enum Sounds{
    LOGIN   = 0,
    PASS    = 1,
    WRONG   = 2,
    START   = 3
};

class GoService : public QObject
{
    Q_OBJECT
public:
    GoService(QObject* parent=0);
    ~GoService();

    void vibrate(int duration, qreal intensity);
    void loadConfig();
    void activate();

public slots:
    void onChangeOrientationChange(int state);
    void powerBtnDoubleClick();
    void startApp();
    void timeOut();

private:
    Orientation* orientation;
    BinaryTree* binaryTree;
    QMediaPlaylist* playlist;
    QMediaPlayer* player;
    QTimer* timer;
    QTimer* killerTimer;
    QFeedbackHapticsEffect* rumble;
};

#endif // GOSERVICE_H
