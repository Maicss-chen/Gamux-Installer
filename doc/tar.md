# tar 解包

相关文件：
- utils/tar.h
- utils/TarFile.h 
- utils/TarFile.cpp

其中`tar.h`取自[https://www.gnu.org/software/tar/manual/html_node/Standard.html](https://www.gnu.org/software/tar/manual/html_node/Standard.html)

我对这个页面进行了简单翻译：[https://maicss-chen.github.io/post.html#Tar.md](https://maicss-chen.github.io/post.html#Tar.md)

其他两个文件定义了一个类`TarFile.h`，程序中通过调用该类的对象来实现对包的解析。

## Tar包格式

tar包分为`标头`和`文件数据`两部分，标头的大小是512字节，文件数据是512的倍数。打包多个文件时，文件内部排列方式是：`A标头|A数据|B标头|B数据...`。每块数据没有明确的分隔符，所有数据连续排列。

标头中内容的定义在`tar.sh`中的`struct posix_header`，但由于标准不同，其末尾的保留部分可能会被使用，如其中的`struct star_header`。

要想将其中的数据转换成对应的结构体，可直接进行指针的强制转换，如：

```cpp
const int block_size{ 512 };
unsigned char buf[block_size];
posix_header* header = (posix_header*)buf;
```

在标头数据中，存在size字段，该字段规定了该标头后紧随的文件数据尺寸，按照此size对数据进行读取即可，该文件数据的末端紧接的就是下一个文件的标头。

另外，通常情况下，一个tar文件的末尾会被填充1024字节的0，以此作为整个tar文件的结束。

## 本程序中读取tar的方式

想要实现从一个文件中，将部分数据看作一个tar包去解析，就需要有明确的起始位置，在本程序中，要从一个sh脚本中读取tar数据，脚本的结构是`脚本内容|游戏内容tar包数据|安装器tar包数据`
其中，脚本内容和游戏内容之间必须存在换行符。

脚本的头部应当预先写入一些数值，包括脚本内容所占行数，和安装器tar数据所占行数。

其中前者容易获取，在脚本编辑器中即可得到，该行数应当位脚本内容总行数（包含末尾的空行）

后者需要使用命令：
```shell
wc -l <安装器的tar包>
```

脚本如下：

```shell
#!/bin/bash
SCRIPT_ROW_COUNT=20 # 这个值务必设置为最后一行(算空行)的行数
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
exit $ret # 下面这里必须有空行，且该空行中不能有任何内容，包括空格和注释。

```

前面说到，该程序需要知道在.sh文件中游戏tar包数据的起始位置，这里就可以根据脚本行数推断出来。因此，当运行此安装器时，需要传入.sh自身的路径和脚本行数两个参数，程序内通过传入的行数推算出字节数。

## 打包示例

### 准备脚本

首先准备脚本，可复制上边的脚本（不要丢掉末尾的空行），命名为`setup.sh`。


### 准备安装器

然后准备安装器的二进制文件，命名为这种格式：`installer_<架构>`，如`installer_x86_64`

然后将其打包到一个tar包中：

```shell
tar -cf installer.tar installer_*
```

此时得到了一个`installer.tar`

然后得到该文件的总行数：

```shell
wc -l installer.tar
```

将得到的数字写入到setup.sh中的`INSTALL_ROW_COUNT`变量中。

### 准备游戏数据包：

建立一个文件夹内容如下：

```
.
├── config.json
├── data
├── game
├── game.desktop
└── README.txt
```

config.json
```json
{
  "name": "GTA3",
  "version": "3.0",
  "desktopFile": "game.desktop",
  "packageName": "gta3",
  "data": "data",
  "game": [
  	{
  		"arch":"x86_64",
  		"path":"game"
  	}
  ],
  "readme": "README.txt"
}
```
game.desktop
```
[Desktop Entry]
Name=侠盗猎车手3
Exec={{target}}/AppRun
Icon={{target}}/game.png
Type=Application
Categories=Games;
```

若仅支持但架构，则无所谓将游戏内容放在`data`还是`game`目录下。可以将其放在其中一个目录，另一个目录留空即可。

然后使用命令将其打包：

```shell
tar -cf gta3.tar *
```

### 组装

将这三个文件组装即可：

```shell
cat setup.sh gta3.tar > gta3.sh
echo -e "\n" >> gta3.sh
cat installer.tar >> gta3.sh
```
