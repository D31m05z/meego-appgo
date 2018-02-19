#!/bin/sh

if pkill GoService; then
    echo "killed"
    cat /opt/AppGo/base/off.desktop >/usr/share/applications/AppGo_harmattan.desktop
else
    echo "starting"
    cat /opt/AppGo/base/on.desktop >/usr/share/applications/AppGo_harmattan.desktop
    pkill AppGo
    /opt/AppGo/base/GoService 
fi
