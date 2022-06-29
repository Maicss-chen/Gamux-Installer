//
// Created by maicss on 22-6-24.
//

#include "utils.h"
#include "stdlib.h"
#include <QMessageBox>
#include <QFileInfo>
#include <sys/stat.h>
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