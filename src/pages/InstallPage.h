//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_INSTALLPAGE_H
#define GAMEINSTALLER_INSTALLPAGE_H
#include <QProgressBar>
#include <QTextEdit>
#include <QThread>
#include <QLabel>

#include "../widgets/GButton.h"
#include "../widgets/GProgressBar.h"

class InstallPage : public QWidget{
    Q_OBJECT
public:
    explicit InstallPage(QWidget *parent);
    void showed();
signals:
    void startInstall();
private:
    GProgressBar *progressBar;
    QLabel *label_tip;
    QThread *installThread;
    QString out;
    GButton *btn_finish;
    long m_count, m_now;
};


#endif //GAMEINSTALLER_INSTALLPAGE_H
