//
// Created by maicss on 22-7-3.
//

#include "Task.h"
#include <QFile>
#include <QTemporaryDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QProcess>
#include <sys/stat.h>

void Task::setConfig(Task::Config c) {
    config = c;
}

Task::Task() {

}

void Task::start() {
    // 创建临时文件夹
    QTemporaryDir temporaryDir;
    temporaryDir.setAutoRemove(false);
    if (!temporaryDir.isValid()){
        emit failed("临时文件夹创建失败！");
    }
    QDir workDir(temporaryDir.path());
    workDir.mkdir("data");
    // 扫描所有游戏资源文件
    for (auto &gameDir : config.gameDir) {
        lsDir(gameDir.directory,&gameDir.list,"",GAME);
    }

    // 将游戏内容复制到对应目录
    for (auto item : config.gameDir) {
        workDir.mkdir("game_"+item.arch);
        int p = 1;
        for (auto f: item.list) {
            emit updateProgress(p,item.list.count(),"复制："+f.path);
            p++;
            QString out = workDir.path()+"/game_"+item.arch +"/"+f.path;;
            QFile file(item.directory + "/" +f.path);
            mkdirP(getDirPath(out));
            file.copy(out);
        }
    }

    // 处理多个游戏架构目录中的相同文件
    int p = 1;
    for (auto &item : config.gameDir.at(0).list) {
        emit updateProgress(p,config.gameDir.at(0).list.count(),"检查："+item.path);
        p++;
        QString md5 = getMd5(workDir.path()+"/game_"+config.gameDir.at(0).arch +"/"+ item.path);
        bool flag = true;
        for (int i = 1; i<config.gameDir.count(); i++) {
            bool flag2 = false;
            for (auto &item2 : config.gameDir.at(i).list) {
                if (item.path == item2.path
                    && md5 == getMd5(workDir.path()+"/game_"+config.gameDir.at(i).arch+"/"+item2.path))
                {
                    flag2 = true;
                    break;
                };
            }
            flag = flag && flag2;
        }
        if (flag){
            // 共有文件
            QFile file(workDir.path()+"/game_"+config.gameDir.at(0).arch+"/" +item.path);
            mkdirP(getDirPath(workDir.absolutePath()+"/data/"+item.path));
            file.copy(workDir.absolutePath()+"/data/"+item.path);
            for (auto i: config.gameDir) {
                QFile f(workDir.path()+"/game_"+i.arch+"/"+item.path);
                f.remove();
            }
        }
    }

    // 复制其他文件
    emit updateProgress(50,100,"部署其他文件");
    QFile icon(config.icon);
    icon.copy(workDir.path()+"/data/icon."+ getExtendNameFromPath(icon.fileName()));

    QFile headerImage(config.headerImage);
    headerImage.copy(workDir.path()+"/header."+ getExtendNameFromPath(headerImage.fileName()));

    // 建立配置文件
    emit updateProgress(50,100,"建立配置文件");
    QJsonObject json_config;
    json_config.insert("name", config.name);
    json_config.insert("version", config.version);
    json_config.insert("packageName", config.packageName);
    json_config.insert("desktopFile", "game.desktop");
    json_config.insert("data","data");
    json_config.insert("header","header."+getExtendNameFromPath(headerImage.fileName()));
    json_config.insert("icon","data/icon."+getExtendNameFromPath(icon.fileName()));
    json_config.insert("readmeUrl",README_URL);
    QJsonArray games;
    for (const auto& i : config.gameDir) {
        QJsonObject game_obj;
        game_obj.insert("path","game_" + i.arch);
        game_obj.insert("arch",i.arch);
        games.append(game_obj);
    }
    json_config.insert("game",games);
    QJsonDocument document(json_config);
    QFile config_file(workDir.path()+"/config.json");
    config_file.open(QFile::WriteOnly);
    config_file.write(document.toJson());
    config_file.close();

    emit updateProgress(50,100,"创建快捷方式");
    QFile desktop_file(workDir.path()+"/game.desktop");
    desktop_file.open(QFile::WriteOnly);
    desktop_file.write(buildDesktopFile({
        config.name,
        "{{target}}/icon."+getExtendNameFromPath(icon.fileName()),
        "{{target}}/AppRun"
    }).toUtf8());
    desktop_file.close();

    emit updateProgress(50,100,"资源数据打包");
    std::string cmd = "cd "+workDir.path().toStdString()+" && tar -cf pkg.tar *";
    system(cmd.c_str());

    qDebug()<<installerFile();

    int count = getFileLineCount(this->installerFile());

    QString script = "#!/bin/bash\n"
                     "SCRIPT_ROW_COUNT=19 # 这个值务必设置为最后一行(算空行)的行数\n"
                     "INSTALL_ROW_COUNT="+QString::number(count)+" # 安装器所占行数\n"
                     "TEMP_DIR=/tmp/Gamux\n"
                     "HOST_ARCH=`uname -m`\n"
                     "SELF=`realpath $0`\n"
                     "notify-send \"Gamux\" \"正在解压数据，安装器稍后将自动启动\" -t 5000\n"
                     "if [ -d \"/tmp/Gamux\" ]; then\n"
                     "    rm -r $TEMP_DIR/*\n"
                     "else\n"
                     "    mkdir $TEMP_DIR\n"
                     "fi\n"
                     "tail -n $((INSTALL_ROW_COUNT+1)) $SELF | tar -xC $TEMP_DIR\n"
                     "cd $TEMP_DIR\n"
                     "chmod +x *\n"
                     "echo \"./installer_${HOST_ARCH} $SELF ${SCRIPT_ROW_COUNT}\"\n"
                     "./installer_${HOST_ARCH} $SELF ${SCRIPT_ROW_COUNT}\n"
                     "ret=$?\n"
                     "exit $ret\n";

    emit updateProgress(50,100,"向目标写入执行脚本");
    QString outfilename = config.outDir +"/" +config.name + "_" + config.version + ".sh";
    QFile out(outfilename);
    out.remove();
    out.open(QFile::WriteOnly | QFile::Append);
    out.write(script.toStdString().c_str());

    emit updateProgress(50,100,"向目标写入软件包数据");
    QFile tar(workDir.path() +"/pkg.tar");
    tar.open(QFile::ReadOnly);
    out.write(tar.readAll());
    tar.close();

    emit updateProgress(50,100,"向目标写入安装器");
    out.write("\n");
    QFile installer(installerFile());
    installer.open(QFile::ReadOnly);
    out.write(installer.readAll());
    installer.close();

    out.flush();
    out.close();

    chmod(outfilename.toUtf8(), 0755);

    emit updateProgress(100,100,"完成："+outfilename);
}

QString Task::installerFile() {
    return m_installerFile;
}

void Task::setInstallerFile(QString installerFile) {
    m_installerFile=std::move(installerFile);
}
