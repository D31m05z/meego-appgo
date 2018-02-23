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

#ifndef GOSYSTEM_H
#define GOSYSTEM_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QHash>
#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>

#include <MComponentData>
#include <MNotification>

#include <iostream>

#include "orientation.h"
#include "binarytree.h"

using namespace std;

struct Item
{
    QString exec;
    int code[7];
    QString command;
};

class GoSystem : public QObject
{
    Q_OBJECT
public:
    GoSystem(QObject *parent=0);
    ~GoSystem();
    void getData();
    void processDesktopFile(QString fileName);
    void loadConfig();
    void codeToString();

    Q_INVOKABLE void orientationEnable(bool enable);
    Q_INVOKABLE bool isPassRecording();
    Q_INVOKABLE void startPasswordRecord();
    Q_INVOKABLE void stopPasswordRecord();
    Q_INVOKABLE void setSelectedItem(QString name);
    Q_INVOKABLE void beforeExit();
    Q_INVOKABLE void removeCommand(QString name);
    Q_INVOKABLE void exitAndActivating();
    Q_INVOKABLE bool haveCommand(QString name);
    Q_INVOKABLE void refresh();

public slots:
    void onChangeOrientationChange(int state);
    void writeCommands();
    void activating();
signals:
    void addApp(QVariant, QVariant, QVariant,QVariant);

private:
    bool passRecord;
    int codeNumber;
    bool hasConfigFile;

    QObject* root;
    Orientation* orientation;
    QString selected;
    QHash<QString,Item> applications;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
};

#endif // GOSYSTEM_H
