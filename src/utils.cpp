//
// Created by maicss on 22-6-24.
//

#include "utils.h"
#include "stdlib.h"
#include <QMessageBox>
#include <QFileInfo>
#include <sys/stat.h>
#include <QTextStream>
#include <QDir>
QString getDirPath(QString filename) {
    return filename.left(filename.lastIndexOf('/'));
}

QString HomeDir() {
    return getenv("HOME");
}

void MessageBoxExec(QString title, QString content, QMessageBox::Icon icon) {
    QMessageBox messageBox;
    messageBox.setWindowTitle(title);
    messageBox.setText(content);
    messageBox.setIcon(icon);
    messageBox.exec();
}
bool mkdirP(QString path) {
    QFileInfo info(path);
    if (info.exists()){
        return true;
    }
    QVector<QString> paths;
//    paths.push_back(path);
    do {
        paths.push_front(path);
        path = getDirPath(path);
        info.setFile(path);
    } while (!info.exists());

    for (auto& d : paths) {
        if(mkdir(d.toStdString().c_str(),0755)!=0) return false;
    }
    return true;
}

void lsDir(QString path, QVector<Entry> *list, QString front, Category category) {
    QDir dir(path);
    for(auto entry : dir.entryList()){
        if (entry == "." || entry == "..") continue;
        QFileInfo info(path + "/" + entry);
        if (info.isDir()){
            list->append(Entry{front+entry,DIR,"",category});
            lsDir(path+"/"+entry,list,front+entry+"/",category);
            continue;
        }
        if (info.isSymLink()){
            list->append(Entry{front+entry,SYMLINK,info.symLinkTarget(),category});
            continue;
        }
        list->append(Entry{front+entry,NORMAL_FILE,"",category});
    }
}