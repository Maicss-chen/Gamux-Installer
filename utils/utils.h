//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_UTILS_H
#define GAMEINSTALLER_UTILS_H

#include <QString>
#include <QMessageBox>

enum FileType {
    NORMAL_FILE,
    DIR,
    SYMLINK
};
enum Category {
    GAME,
    DATA
};
struct Entry {
    QString path;
    FileType type;
    QString target;
    Category category;
};

QString getDirPath(QString filename);

QString HomeDir();
void MessageBoxExec(QString title, QString content, QMessageBox::Icon icon = QMessageBox::Icon::NoIcon);
bool mkdirP(QString path);
void lsDir(QString, QVector<Entry> *, QString front, Category category);
QString getMd5(QString path);
QString chooseDirectory();
QString chooseFile(QString filter);

#endif //GAMEINSTALLER_UTILS_H
