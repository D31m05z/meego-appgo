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

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <QDebug>
#include <QProcess>
#include <MComponentData>
#include <MNotification>

struct Node
{
    int data;
    QString exec;
    Node* nodes[7];

    Node(int dataNew)
    {
        data = dataNew;
        for (int i = 0; i < 7; ++i) {
            nodes[i] = NULL;
        }
    }
};

class BinaryTree
{
    Node* lastFound;
private:

    void Insert(int newData, Node* &theRoot)
    {
        if(theRoot == NULL) {
            theRoot = new Node(newData);
            //  qDebug() << "new"<<newData;
            last = theRoot;

            return;
        }

        if(newData == theRoot->data) {
            last = theRoot;
        } else {
            Insert(newData, theRoot->nodes[newData]);
        }
    }


    void PrintTree(Node* theRoot, int level)
    {
        QString extraTab;
        level++;
        if(theRoot != NULL) {
            for (int j = 0; j < level; ++j) {
                extraTab+="-";
            }

            qDebug()<< "L"<<level<<qPrintable(extraTab )<<"|"<<theRoot->data<<theRoot->exec;
            for (int i = 0; i < 7; ++i) {
                PrintTree(theRoot->nodes[i],level);
            }
        }
    }

    bool FindCommand(Node* theRoot, int command, int level)
    {
        level++;
        //qDebug()<<"inCommand:"<<command<<" level:"<<level;

        if(theRoot != NULL) {
            for (int i = 0; i < 7; ++i) {
                if(theRoot->nodes[i] != NULL)
                    if(command == theRoot->nodes[i]->data) {
                        qDebug() << "FOUND COMMAND:" << command;
                        lastFound = theRoot->nodes[i];
                        return true;
                    } else lastFound = root;
            }
        }
        return false;
    }

    bool canExecute(Node* last)
    {
        if(last->exec.size() != 0) {
            qDebug() << "can execute:" << last->exec;
            return true;
        }
        return false;
    }

    void execute(Node* last)
    {
        QProcess process;
        qDebug()<<"STARTING>" << last->exec;

        /*  MNotification notification(MNotification::DeviceEvent, "", QObject::tr("starting..."));
         notification.setImage("icon-m-user-guide");
         notification.publish();*/
        process.startDetached(last->exec);
    }

public:
    Node* root;
    Node* last;

    BinaryTree()
    {
        root = NULL;
        last = NULL;
        lastFound = NULL;
    }

    void AddItem(int newData, bool append)
    {
        if(append)
            Insert(newData, last);
        else
            Insert(newData, root);

        //    qDebug() << "ROOT" << root->data;
        //    qDebug() << "LAST" << last->data;
    }

    void AddItem(QString program)
    {
        last->exec = program;
    }

    void PrintTree()
    {
        PrintTree(root,0);
    }

    bool FindCommand(int cmd)
    {
        if(lastFound == NULL || cmd ==0)
            lastFound = root;

        return FindCommand(lastFound,cmd,0);
    }

    bool canExecute()
    {
        return canExecute(lastFound);
    }

    void execute()
    {
        execute(lastFound);
    }
};

#endif // BINARYTREE_H
