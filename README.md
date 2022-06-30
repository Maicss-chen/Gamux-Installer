# Gameux 游戏安装器

## 编译

需要：Qt5.4以上

```shell
mkdir build
cmake ..
make
```

## 使用

```shell
cd src
./game-installer <配置文件名>
```

## 配置文件示例

```json
{
  "name": "Gameux",
  "version": "1.0",
  "desktopFile": "cn.linuxgame.desktop",
  "data": "data",
  "game": "game_x86",
  "readme": "安装包第一页显示的内容，可以展示用户协议等。"
}
```

- name: 游戏名，将显示在安装器标题栏上
- version： 版本号，同游戏名显示在标题栏上
- desktopFile: desktop文件路径
- data：游戏数据目录路径
- game：游戏程序目录路径
- readme：安装器的第一页显示的文字

> 1. 其中涉及到“路径”的选项，应当填写相对于配置文件目录的相对路径。
> 2. data和game目录最终将被合并复制到安装目录，若这两个目录中的文件存在重复，则data目录中的将被覆盖。

## desktop文件

在编写desktop文件时，由于无法确定安装位置，因此需要使用`{{target}}`来代替安装位置，安装程序安装后将自动将其替换为安装路径。

```
[Desktop Entry]
Name=Gameux
Icon={{target}}/.icon.svg
Comment=Gameux
Exec="{{target}}/start.sh" %u
Version=1.0
Type=Application
Categories=Game;
Terminal=false
StartupNotify=true
```