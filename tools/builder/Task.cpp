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

    // 建立配置文件
    QJsonObject json_config;
    json_config.insert("name", config.name);
    json_config.insert("version", config.version);
    json_config.insert("packageName", config.packageName);
    json_config.insert("desktopFile", "game.desktop");
    json_config.insert("data","data");
    json_config.insert("readme","README.txt");
    QJsonArray games;
    for (auto i : config.gameDir) {
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

    // 复制其他文件
    QFile desktop(config.desktopFilePath);
    desktop.copy(workDir.path()+"/game.desktop");

    QFile readme(config.readmeFilePath);
    readme.copy(workDir.path()+"/README.txt");

    QFile installer_x86_64(config.installer_x86_64);
    installer_x86_64.copy(workDir.path()+"/installer_x86_64");

    QFile installer_aarch(config.installer_aarch64);
    installer_aarch.copy(workDir.path()+"/installer_aarch64");

    std::string cmd = "cd "+workDir.path().toStdString()+" && tar -cf pkg.tar *";

    system(cmd.c_str());
    QString script = "#!/bin/bash\n"
                     "SCRIPT_ROW_COUNT=17 # 这个值务必设置为脚本内容行数-1（不算末尾的空行）\n"
                     "TEMP_DIR=/tmp/Gamux\n"
                     "HOST_ARCH=`uname -m`\n"
                     "notify-send \"Gamux\" \"正在解压数据，安装器稍后将自动启动\" -t 5000\n"
                     "line=`wc -l $0 | awk '{print $1}'`\n"
                     "line=`expr $line - $SCRIPT_ROW_COUNT`\n"
                     "if [ -d \"/tmp/Gamux\" ]; then\n"
                     "    rm -r $TEMP_DIR/*\n"
                     "else\n"
                     "    mkdir $TEMP_DIR\n"
                     "fi\n"
                     "tail -n $line $0 | tar -xC $TEMP_DIR\n"
                     "cd $TEMP_DIR\n"
                     "chmod +x ./installer_${HOST_ARCH}\n"
                     "./installer_${HOST_ARCH} ./config.json\n"
                     "ret=$?\n"
                     "exit $ret\n";

    QString outfilename = config.outDir +"/" +config.name + "_" + config.version + ".sh";
    QFile out(outfilename);
    out.remove();
    out.open(QFile::WriteOnly | QFile::Append);
    out.write(script.toStdString().c_str());

    QFile tar(workDir.path() +"/pkg.tar");
    tar.open(QFile::ReadOnly);
    out.write(tar.readAll());
}
