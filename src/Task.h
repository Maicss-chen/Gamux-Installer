//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_TASK_H
#define GAMEINSTALLER_TASK_H

#include <QObject>
#include <QString>
#include "TarFile.h"

class Task : public QObject{
    Q_OBJECT
    struct Config {
        QString readme; // 安装器第一页展示的内容
        QString name; // 游戏名称
        QString version; // 游戏版本
        QString game; // 游戏二进制程序包
        QString data; // 游戏资源包
        QString desktopFile; // 快捷方式
        QString selfDir; // 配置文件所在目录
    };
public slots:
    void setInstallTargetDir(QString target);
    void setAddDesktopIcon(bool add);
    void serAddLauncherIcon(bool add);
    void install();
    bool loadConfigFile(QString file);

public:
    static Task task;
    Config config;

signals:
    void updateProgress(int now, int count, QString message);
    void failed(QString message);
    void success();
private:
    QString installTargetDir;
    bool addDesktopIcon;
    bool addLauncherIcon;
    TarFile *tarFile;

};

#endif //GAMEINSTALLER_TASK_H
