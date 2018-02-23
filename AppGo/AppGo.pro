folder_01.source = base
DEPLOYMENTFOLDERS = folder_01

QT += declarative
CONFIG += qdeclarative-boostable

CONFIG += meegotouch mobility

MOBILITY += multimedia feedback sensors

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    gosystem.cpp \
    orientation.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += gosystem.h \
    orientation.h \
    binarytree.h \
    powerbuttonlistener.h

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qml/Storage.js \
    qml/MainPage.qml.autosave \
    qml/SettingsAccount.qml \
    qml/Powersave.qml \
    qml/Mainwindow.qml \
    qml/MainPage.qml \
    qml/main.qml \
    qml/AppListPage.qml \
    qml/Applist.qml \
    qml/App.qml \
    qml/AboutPage.qml

RESOURCES += \
    resources.qrc
