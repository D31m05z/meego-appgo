
CONFIG += mobility meegotouch link_pkgconfig
PKGCONFIG += gq-gconf libresourceqt1 hal glib-2.0 dbus-glib-1
MOBILITY = multimedia feedback messaging sensors

QT     += gui network

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    goservice.cpp \
    orientation.cpp \
    powerbuttonlistener.cpp

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/GoService/bin
    INSTALLS += target
}

HEADERS += goservice.h \
    orientation.h \
    binarytree.h \
    powerbuttonlistener.h

RESOURCES += \
    resources-service.qrc

contains(MEEGO_EDITION,harmattan) {
    desktopfile.files = GoService.desktop
    desktopfile.path = /usr/share/applications
    INSTALLS += desktopfile
}

contains(MEEGO_EDITION,harmattan) {
    icon.files = GoService.png
    icon.path = /usr/share/icons/hicolor/80x80/apps
    INSTALLS += icon
}
