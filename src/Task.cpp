//
// Created by maicss on 22-6-24.
//

#include "Task.h"
#include "utils.h"
#include <iostream>
#include <QSysInfo>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QApplication>
#include <QVector>
#include <QDir>
#include <QJsonArray>
#include <QStandardPaths>

using namespace std;
Task Task::task;

void Task::setInstallTargetDir(QString target) {
    installTargetDir = target;
}

void Task::setAddDesktopIcon(bool add) {
    addDesktopIcon = add;
}

void Task::serAddLauncherIcon(bool add) {
    addLauncherIcon = add;
}

void Task::install() {
    enum FileType {
        FILE,
        DIR,
        SymLink
    };
    struct Entry {
        QString path;
        FileType type;
        QString target;
    };
    QVector<Entry> file_list;
    std::function<void(QString, QVector<Entry> *, QString front)> ls;
    ls = [&](QString path, QVector<Entry> *list, QString front) {
        QDir dir(path);
        for(auto entry : dir.entryList()){
            if (entry == "." || entry == "..") continue;
            QFileInfo info(path + "/" + entry);
            if (info.isDir()){
                list->append(Entry{front+entry,DIR,""});
                ls(path+"/"+entry,list,front+entry+"/");
            }
            if (info.isFile()) {
                list->append(Entry{front+entry,FILE,""});
            }
            if (info.isSymLink()) {
                list->append(Entry{front+entry,SymLink,""});
            }
        }
    };
    ls(config.selfDir + "/" + config.data, &file_list, "");
    ls(config.selfDir+"/"+config.game,&file_list,"");
    for (int i = 0; i < file_list.size(); i++){
        Entry entry = file_list.at(i);
        if (entry.type == DIR) {
            QString targetDir = installTargetDir +"/"+ entry.path;
            emit updateProgress(i, file_list.size(), "创建：" + entry.path);
            if (!mkdirP(targetDir)){
                emit failed("文件夹"+targetDir+"创建失败");
                return;
            }
            continue;
        }

        QFile file(config.selfDir + "/"+config.game+"/" + entry.path);
        QFileInfo info(file);
        file.copy(task.installTargetDir + "/" + entry.path);
        emit updateProgress(i, file_list.size(), "复制：" + entry.path);
    }

    // build desktopfile
    QFile srcDesktopFile(config.selfDir + "/" + config.desktopFile);
    srcDesktopFile.open(QFile::ReadOnly);
    QString desktopText = srcDesktopFile.readAll().replace("{{target}}",installTargetDir.toStdString().c_str());
    srcDesktopFile.close();
    if (addDesktopIcon){;
        QFile desktopFile;
        desktopFile.setFileName( QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"/"+config.game+".desktop");
        desktopFile.open(QFile::WriteOnly);
        desktopFile.write(desktopText.toStdString().c_str());
        desktopFile.close();
    }
    if (addLauncherIcon){
        QFile desktopFile( HomeDir()+"/.local/share/applications/"+config.game+".desktop");
        desktopFile.open(QFile::WriteOnly);
        desktopFile.write(desktopText.toStdString().c_str());
        desktopFile.close();
    }
    emit updateProgress(file_list.size(), file_list.size(), "安装完成");
}

bool Task::loadConfigFile(QString file) {
    QFileInfo fileInfo(file);
    if (!fileInfo.exists()){
        MessageBoxExec("加载失败", "配置文件错误：没有找到配置文件");
        return false;
    }

    config.selfDir = getDirPath(file);

    QFile configFile(file);

    configFile.open(QFile::ReadOnly);
    auto jsonDoc = QJsonDocument::fromJson(configFile.readAll());
    auto obj = jsonDoc.object();
    config.readme = obj.value("readme").toString();
    config.name = obj.value("name").toString();
    config.version = obj.value("version").toString();
    config.desktopFile = obj.value("desktopFile").toString();
    config.data = obj.value("data").toString();
    auto gameList = obj.value("game").toArray();
    QString arch = QSysInfo::currentCpuArchitecture();
    bool flag = false;
    for (auto game : gameList){
        if(game.toObject().value("arch") == arch){
            config.game = game.toObject().value("path").toString();
            flag = true;
        }
    }
    if (!flag){
        MessageBoxExec("加载失败", "该游戏不支持\""+arch+"\"架构！");
        return false;
    }

    if (config.name.isEmpty()) {
        MessageBoxExec("加载失败", "配置文件错误：name配置项为空！");
        return false;
    }
    if (config.version.isEmpty()) {
        MessageBoxExec("加载失败", "配置文件错误：version配置项为空！");
        return false;
    }
    if (config.readme.isEmpty()) {
        MessageBoxExec("加载失败", "配置文件错误：readme配置项为空！");
        return false;
    }
    if (config.desktopFile.isEmpty()) {
        MessageBoxExec("加载失败", "配置文件错误：desktopFile配置项为空！");
        return false;
    }
    if (config.game.isEmpty()) {
        MessageBoxExec("加载失败", "配置文件错误：game配置项为空！");
        return false;
    }
    if (config.data.isEmpty()) {
        MessageBoxExec("加载失败", "配置文件错误：data配置项为空！");
        return false;
    }
    cout<<"Current cpu architecture: "<<arch.toStdString()<<endl;
    cout<<"=========config===========\n"
        <<"name: "<< config.name.toStdString()<<endl
        <<"version: "<< config.version.toStdString()<<endl
        <<"desktopFile: "<< config.desktopFile.toStdString()<<endl
        <<"game: "<< config.game.toStdString()<<endl
        <<"data: "<< config.data.toStdString()<<endl
        <<"==========================\n";
    return true;
}
