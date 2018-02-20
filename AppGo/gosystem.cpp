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

#include "gosystem.h"

GoSystem::GoSystem(QObject *parent)
    :QObject(parent)
    , passRecord(false)
    , codeNumber(0)
    , hasConfigFile(false)
{
    root = parent;
    QObject *page = root->findChild<QObject *>("mainwindow");
    qDebug() << "I found this page: "  << page;

    orientation = new Orientation(parent);
    connect(orientation,SIGNAL(orientationChanged(int)),SLOT(onChangeOrientationChange(int)));

    root->setProperty("password","start: FACE UP\n");

    loadConfig();

    connect(this, SIGNAL(addApp(QVariant,QVariant,QVariant,QVariant)), page, SLOT(addNewIcon(QVariant,QVariant,QVariant,QVariant)));
    getData();

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("/opt/AppGo/base/login.wav"));
    playlist->addMedia(QUrl::fromLocalFile("/opt/AppGo/base/beep.wav"));

    playlist->setCurrentIndex(0);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->setVolume(50);
}

GoSystem::~GoSystem()
{
    delete orientation;
    delete passFile;
    delete player;
    delete playlist;
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

void GoSystem::loadConfig()
{
    QFile file("/home/user/appgo.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "ERROR: open file";
        hasConfigFile = false;
        return;
    }

    QString name;
    Item item;

    for (int i = 0; i < 7; ++i) {
        item.code[i] = 0;
    }

    int index = 0;
    while (!file.atEnd()) {
        QString line(file.readLine());
        line = rstrip(line);

        index++;
        if(index==1){
//           qDebug() << line;
            name = line;
        }else if(index==2){
            QStringList codes = line.split(" ");
            for (int i = 0; i < codes.size(); ++i) {
                //qDebug() << codes[i];
                if(codes[i]=="")
                    item.code[i]=0;
                else
                    item.code[i]=codes[i].toInt();
            }
        }else if (index == 3 ){
            //qDebug() << line;
            item.exec = line;
            applications.insert(name,item);
            index=0;
        }
    }

    hasConfigFile = true;
}

void GoSystem::processDesktopFile(QString fileName)
{
    QFile file("/usr/share/applications/" + fileName);

    QString name=0;
    QString exec=0;
    QString icon=0;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QString line(file.readLine());

        line = rstrip(line);

        if(line.contains("Exec=")){
            line.replace("Exec=","");
            exec = line;
            qDebug() << "++Exec:" << line << endl;
        }else if(line.contains("Name=")){
            line.replace("Name=","");
            name = line;
            qDebug() << "++Name:" << line << endl;
        }else if(line.contains("Icon=") && !line.contains("X-Window")){
            line.replace("Icon=","");
            icon = line;
            qDebug() << "++Icon:" <<line << endl;
        }
    }

    if(name!=0 && exec !=0 && icon !=0) {
        if(hasConfigFile ){
            Item i;
            i.exec = exec;
            for (int j = 0; j < 7; ++j) {
                i.code[j] = 0;
            }

            i.command = "start: FACE UP\n";

            applications.insert(name,i);
            qDebug() << "-------$ADD="<<name<<"------------------------";
        }

        bool active = false;
        if(applications[name].code[0]!=0)
            active = true;

        emit addApp(exec, name, icon, active);
    }
}

void GoSystem::getData()
{
    qDebug() << "getData called" << endl;
    QDir dir;
    dir.setPath("/usr/share/applications/");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        processDesktopFile(fileInfo.fileName());
    }
}

void GoSystem::writeCommands()
{
    qDebug() << "CREATE COMMAND FILE" << endl;
    passFile = new QFile("/home/user/appgo.txt");

    if (!passFile->open(QFile::WriteOnly | QIODevice::Text)) {
        qDebug() << "FILE CREATE FAIL" << endl;
    }

    QTextStream out(passFile);

    QList<QString> appList = applications.keys();
    for (int i = 0; i < appList.size(); ++i) {
        out << appList.at(i)<<endl;
        for (int j = 0; j < 7; ++j) {
            //if(applications[appList[i]].code[j] !=0 )
            out << applications[appList[i]].code[j] << " ";
        }

        //qDebug()<<"WRITE - EXEC>"<<applications[appList.at(i)].exec;
        out << endl << applications[appList.at(i)].exec << endl;
    }

    passFile->close();
}

void GoSystem::beforeExit()
{
    emit writeCommands();
}

void GoSystem::codeToString()
{
    applications[selected].command = "start: FACE UP\n";
    for (int i = 0; i < 7; ++i) {
        switch(applications[selected].code[i])
        {
        case QOrientationReading::TopUp:
            applications[selected].command.append("Top Up\n");
            break;
        case QOrientationReading::TopDown:
            applications[selected].command.append("Top Down\n");
            break;
        case QOrientationReading::LeftUp:
            applications[selected].command.append("Left Up\n");
            break;
        case QOrientationReading::RightUp:
            applications[selected].command.append("Right Up\n");
            break;
        case QOrientationReading::FaceDown:
            applications[selected].command.append("Face Down\n");
            break;
        case QOrientationReading::FaceUp:
            applications[selected].command.append("Face Up\n");
            break;
        default:
            break;
        }
    }
    root->setProperty("password",applications[selected].command);
}

void GoSystem::activating()
{
    //TODO: test it!!
    beforeExit();

    qDebug() << "START SERVICE"<<endl;
    system("/bin/sh /opt/AppGo/base/service.sh");
}

///////////INVOKE
bool GoSystem::haveCommand(QString name)
{
    if(applications[name].code[0] != 0)
        return true;

    return false;
}

void GoSystem::exitAndActivating()
{
    qDebug() << "ACTIVATING...";
    QTimer::singleShot(2000,this,SLOT(activating()));
    MNotification notification(MNotification::DeviceEvent, "", QObject::tr("Activating... after activating the AppGo exiting!"));
    notification.setImage("icon-m-user-guide");
    notification.publish();
}

void GoSystem::orientationEnable(bool enable)
{
    qDebug() << "orientationEnable:" << enable << endl;
    orientation->setActive(enable);
}

bool GoSystem::isPassRecording()
{
    qDebug() << "isPassRecording" << endl;
    return passRecord;
}

void GoSystem::startPasswordRecord()
{
    passRecord  = true;
    root->setProperty("isPassRecording",true);

    for (int i = 0; i < 7; ++i) {
        applications[selected].code[i] = 0;
    }
    applications[selected].command = "start: FACE UP\n";
    root->setProperty("password",applications[selected].command);
    codeNumber = 0;
}

void GoSystem::stopPasswordRecord()
{
    qDebug() << "stopPasswordRecord" << endl;
    passRecord  = false;
    root->setProperty("isPassRecording",false);
}

void GoSystem::onChangeOrientationChange(int state)
{
    qDebug() << "onChangeOrientationChange:"<<passRecord << " STATE: " <<state;
    if(!passRecord)
        return;

    playlist->setCurrentIndex(1);
    player->play();

    applications[selected].code[codeNumber++] = state;

    switch(state)
    {
    case QOrientationReading::TopUp:
        applications[selected].command.append("Top Up\n");
        break;
    case QOrientationReading::TopDown:
        applications[selected].command.append("Top Down\n");
        break;
    case QOrientationReading::LeftUp:
        applications[selected].command.append("Left Up\n");
        break;
    case QOrientationReading::RightUp:
        applications[selected].command.append("Right Up\n");
        break;
    case QOrientationReading::FaceDown:
        applications[selected].command.append("Face Down\n");
        break;
    case QOrientationReading::FaceUp:
        applications[selected].command.append("Face Up\n");
        break;
    default:
        break;
    }
    root->setProperty("password",applications[selected].command);

    if(codeNumber == 7)
        stopPasswordRecord();
}

void GoSystem::setSelectedItem(QString name)
{
    qDebug() << "setSelectedItem:"<<name << endl;
    selected = name;

    //qDebug()<<"EXEC>"<<applications[name].exec;

    codeToString();
}

void GoSystem::removeCommand(QString name)
{
    qDebug() << "removeCommand:"<<name << endl;

    for (int i = 0; i < 7; ++i) {
        applications[name].code[i] = 0;
    }
}

void GoSystem::reflash()
{
    system("rm /home/user/appgo.txt");
}
