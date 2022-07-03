#!/bin/bash
SCRIPT_ROW_COUNT=17 # 这个值务必设置为脚本内容行数-1（不算末尾的空行）
TEMP_DIR=/tmp/Gamux
HOST_ARCH=`uname -m`
notify-send "Gamux" "正在解压数据，安装器稍后将自动启动" -t 5000
line=`wc -l $0 | awk '{print $1}'`
line=`expr $line - $SCRIPT_ROW_COUNT`
if [ -d "/tmp/Gamux" ]; then
    rm -r $TEMP_DIR/*
else
    mkdir $TEMP_DIR
fi
tail -n $line $0 | tar -xC $TEMP_DIR
cd $TEMP_DIR
chmod +x ./installer_${HOST_ARCH}
./installer_${HOST_ARCH} ./config.json
ret=$?
exit $ret
