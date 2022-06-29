//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_INSTALLPAGE_H
#define GAMEINSTALLER_INSTALLPAGE_H
#include "Page.h"
#include <QProgressBar>
#include <QTextEdit>
#include <QThread>

class InstallPage : public Page{
    Q_OBJECT
public:
    explicit InstallPage(QWidget *parent);
private:
    void showed() override;
    void updateData() override;
    QProgressBar *progressBar;
    QTextEdit *textEdit;
    QThread *installThread;
};


#endif //GAMEINSTALLER_INSTALLPAGE_H
