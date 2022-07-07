#!/bin/bash
SCRIPT_ROW_COUNT=23 # 这个值务必设置为最后一行的行数+1
INSTALL_ROW_COUNT=14509 # 安装器所占行数
DATA_SIZE=1234923520 # 数据字节数
TEMP_DIR=/tmp/Gamux
HOST_ARCH=`uname -m`
SELF=`realpath $0`
notify-send "Gamux" "正在解压数据，安装器稍后将自动启动" -t 5000
line=`wc -l $SELF | awk '{print $1}'`
line=`expr $SCRIPT_ROW_COUNT + $INSTALL_ROW_COUNT`
if [ -d "/tmp/Gamux" ]; then
    rm -r $TEMP_DIR/*
else
    mkdir $TEMP_DIR
fi
sed -n "$SCRIPT_ROW_COUNT,${line}p" $SELF | tar -xC ${TEMP_DIR}
cd $TEMP_DIR
chmod +x *
echo "./installer_${HOST_ARCH} $SELF ${DATA_SIZE}"
./installer_${HOST_ARCH} $SELF ${DATA_SIZE}
ret=$?
exit $ret