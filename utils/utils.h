//
// Created by maicss on 22-6-24.
//

#ifndef SERVER_URL
#define SERVER_URL "http://0.0.0.0:8000/"
#endif

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
QString getDirPath(const QString& filename);
void lsDir(QString, QVector<Entry> *, QString front, Category category);
QString HomeDir();
void MessageBoxExec(const QString& title, const QString& content, QMessageBox::Icon icon = QMessageBox::Icon::NoIcon);
bool mkdirP(QString path);
QString getMd5(const QString& path);
QString chooseDirectory();
QString chooseFile(const QString& filter);
QString getValidParentPath(QString path);
int getFileLineCount(const QString &path);
QString getDataPath();
QString toEasyReadByteSize(qint64 size);

#endif //GAMEINSTALLER_UTILS_H
