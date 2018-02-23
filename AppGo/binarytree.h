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

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <QDebug>

struct Node
{
    int data;
    QString exec;
    Node* nodes[6];

    Node(int dataNew)
    {
        data = dataNew;
        for (int i = 0; i < 6; ++i) {
            nodes[i] = NULL;
        }
    }
};


class BinaryTree
{
    int level;

private:

    void Insert(int newData, Node* &theRoot, int l)
    {
        if(theRoot == NULL) {
            theRoot = new Node(newData);
            qDebug() << "new"<<newData;
            last = theRoot;
            return;
        }

        if(newData == theRoot->data) {
            last = theRoot;
        } else {
            Insert(newData, theRoot->nodes[newData],l);
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
            for (int i = 0; i < 6; ++i) {
                PrintTree(theRoot->nodes[i],level);
            }
        }
    }

public:
    Node* root;
    Node* last;

    BinaryTree()
    {
        root = NULL;
        last = NULL;
        level=0;
    }

    void AddItem(int newData, bool append)
    {
        if(append)
            Insert(newData, last,level);
        else
            Insert(newData, root,level);

        qDebug() << "ROOT" << root->data;
        qDebug() << "LAST" << last->data;
        level++;
        // qDebug() <<"REQUIREST LEVEL"<<level;
    }

    void AddItem(QString program)
    {
        last->exec = program;
    }

    void PrintTree()
    {
        PrintTree(root,0);
    }
};

#endif // BINARYTREE_H
