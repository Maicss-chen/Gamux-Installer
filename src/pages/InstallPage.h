//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_INSTALLPAGE_H
#define GAMEINSTALLER_INSTALLPAGE_H
#include <QProgressBar>
#include <QTextEdit>
#include <QThread>

#include "Page.h"

class InstallPage : public Page{
    Q_OBJECT
public:
    explicit InstallPage(QWidget *parent);
signals:
    void startInstall();
private:
    void showed() override;
    void updateData() override;
    QProgressBar *progressBar;
    QLabel *labelOut;
    QThread *installThread;
    QString out;
    long m_count, m_now;
};


#endif //GAMEINSTALLER_INSTALLPAGE_H
