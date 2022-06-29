//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_UTILS_H
#define GAMEINSTALLER_UTILS_H

#include <QString>
#include <QMessageBox>
QString getDirPath(QString filename);

QString HomeDir();
void MessageBoxExec(QString title, QString content, QMessageBox::Icon icon = QMessageBox::Icon::NoIcon);
bool mkdirP(QString path);

#endif //GAMEINSTALLER_UTILS_H
