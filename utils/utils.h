//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_UTILS_H
#define GAMEINSTALLER_UTILS_H

#include <QString>
#include <QMessageBox>

QString getDirPath(const QString& filename);

QString HomeDir();
void MessageBoxExec(const QString& title, const QString& content, QMessageBox::Icon icon = QMessageBox::Icon::NoIcon);
bool mkdirP(QString path);
QString getMd5(const QString& path);
QString chooseDirectory();
QString chooseFile(const QString& filter);
QString getValidParentPath(QString path);

#endif //GAMEINSTALLER_UTILS_H
