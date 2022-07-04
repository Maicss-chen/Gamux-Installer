//
// Created by maicss on 22-7-3.
//

#ifndef GAMUX_INSTALLER_TASK_H
#define GAMUX_INSTALLER_TASK_H

#include <QObject>
#include "utils.h"

class Task : public QObject{
    Q_OBJECT
public:
    struct GameDir {
        QString arch;
        QString directory;
        QVector<Entry> list;
    };
    struct Config {
        QString name;
        QString version;
        QString packageName;
        QString desktopFilePath;
        QString readmeFilePath;
        QString outDir;
        QVector<GameDir> gameDir;
        QString installer_x86_64;
        QString installer_aarch64;
    };
    Task();
    void setConfig(Config c);
    void start();
signals:
    void updateProgress(int now, int count, QString message);
    void failed(QString message);
    void success();
private:
    Config config;
};


#endif //GAMUX_INSTALLER_TASK_H
