//
// Created by maicss on 22-6-24.
//
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
#include <QTextStream>
#include <QThread>

#include "Task.h"
#include "utils.h"

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>

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
    QVector<QString> uninstall_list;
    mkdirP(installTargetDir);
    uninstall_list.append(installTargetDir);

//    TarFile data((config.selfDir + "/" + config.data).toStdString().c_str());
//    TarFile game((config.selfDir + "/" + config.game).toStdString().c_str());

    size_t dataFileCount = tarFile->getNodeCount(config.data+"/");
    size_t fileCount = dataFileCount;
    fileCount += tarFile->getNodeCount(config.game+"/");



    connect(tarFile, &TarFile::progressReady, [=](size_t now, const QString& filename){
        emit updateProgress(now, dataFileCount, filename);
    });
    tarFile->unpack(installTargetDir,config.data+"/");
    tarFile->disconnect();
//    connect(tarFile, &TarFile::progressReady, [=](size_t now, const QString& filename){
//        emit updateProgress(now + dataFileCount, fileCount, filename);
//    });
//    tarFile->unpack(installTargetDir,config.game+"/");

    // build desktopfile
    QString desktopText = tarFile->readTextFile(config.desktopFile);
    desktopText = desktopText.replace("{{target}}",installTargetDir.toStdString().c_str());
    if (addDesktopIcon){;
        QFile desktopFile;
        QString outPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"/"+config.packageName+".desktop";
        desktopFile.setFileName( outPath);
        desktopFile.open(QFile::WriteOnly);
        desktopFile.write(desktopText.toStdString().c_str());
        uninstall_list.append(outPath);
        desktopFile.close();
    }
    if (addLauncherIcon){
        QString outPath = HomeDir()+"/.local/share/applications/"+config.packageName+".desktop";
        QFile desktopFile( outPath);
        desktopFile.open(QFile::WriteOnly);
        desktopFile.write(desktopText.toStdString().c_str());
        uninstall_list.append(outPath);
        desktopFile.close();
    }

    //build uninstall script
    QFile uninstall_script(installTargetDir + "/uninstall.sh");
    uninstall_script.open(QFile::WriteOnly);
    chmod(uninstall_script.fileName().toStdString().c_str(),0755);
    QTextStream textStream(&uninstall_script);
    textStream<<"#!/bin/bash"<<endl;
    for (const auto& file: uninstall_list) {
        QFileInfo info(file);
        textStream<<"rm -rf "<<info.absoluteFilePath()<<endl;
    }
    textStream<<R"(notify-send "Gamux" ")"+config.name+" 卸载成功\" -t 5000"<<endl;
    textStream.flush();
    uninstall_script.close();
    emit updateProgress(1, 1, "安装完成");
    emit success();
    QThread::currentThread()->exit(0);
}

bool Task::loadConfigFile(const QString& file, long tarSize) {
    tarFile = new TarFile;
    tarFile->open(file.toStdString().c_str(),tarSize);
    QString configContent = tarFile->readTextFile("config.json");
    if (configContent.isEmpty()){
        MessageBoxExec("加载失败", "配置文件错误：没有找到配置文件");
        return false;
    }


    config.selfDir = getDirPath(file);

    auto jsonDoc = QJsonDocument::fromJson(configContent.toUtf8());
    auto obj = jsonDoc.object();
    config.readme = tarFile->readTextFile(obj.value("readme").toString());
    config.name = obj.value("name").toString();
    config.packageName = obj.value("packageName").toString();
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

    cout<<"Current cpu architecture: "<<arch.toStdString()<<endl;
    cout<<"=========config===========\n"
        <<"name: "<< config.name.toStdString()<<endl
        <<"version: "<< config.version.toStdString()<<endl
        <<"packageName: "<< config.packageName.toStdString()<<endl
        <<"desktopFile: "<< config.desktopFile.toStdString()<<endl
        <<"game: "<< config.game.toStdString()<<endl
        <<"data: "<< config.data.toStdString()<<endl
        <<"==========================\n";

    if (!flag){
        MessageBoxExec("无法安装", "该游戏不支持\""+arch+"\"架构！");
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
    if (config.packageName.isEmpty()) {
        MessageBoxExec("加载失败", "配置文件错误：packageName配置项为空！");
        return false;
    }
    return true;
}
