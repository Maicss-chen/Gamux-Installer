#!/bin/bash
SCRIPT_ROW_COUNT=19 # 这个值务必设置为最后一行(算空行)的行数
INSTALL_ROW_COUNT=14330 # 安装器所占行数
TEMP_DIR=/tmp/Gamux
HOST_ARCH=`uname -m`
SELF=`realpath $0`
notify-send "Gamux" "正在解压数据，安装器稍后将自动启动" -t 5000
if [ -d "/tmp/Gamux" ]; then
    rm -r $TEMP_DIR/*
else
    mkdir $TEMP_DIR
fi
tail -n $((INSTALL_ROW_COUNT+1)) $SELF | tar -xC $TEMP_DIR
cd $TEMP_DIR
chmod +x *
echo "./installer_${HOST_ARCH} $SELF ${SCRIPT_ROW_COUNT}"
./installer_${HOST_ARCH} $SELF ${SCRIPT_ROW_COUNT}
ret=$?
exit $ret
