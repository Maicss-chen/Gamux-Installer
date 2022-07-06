//
// Created by maicss on 22-6-24.
//
#include <QApplication>

#include "InstallPage.h"
#include "../Task.h"

InstallPage::InstallPage(QWidget *parent)
    : Page(parent)
    , progressBar(new QProgressBar(this))
    , textEdit(new QTextEdit(this))
    , installThread(new QThread(this))
{
    setTitle("正在安装");
    btn_last->setEnabled(false);
    btn_next->setText("完成");
    btn_next->setEnabled(false);
    btn_next->disconnect();
    connect(btn_next,&QPushButton::clicked,[=](){
        QApplication::exit(0);
    });

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(progressBar);
    layout->addWidget(textEdit);
    mainWidget()->setLayout(layout);

    textEdit->setReadOnly(true);
    connect(&Task::task, &Task::updateProgress,[=](size_t now, size_t count, const QString& message){
        progressBar->setMaximum(int(count));
        progressBar->setValue(int(now));
        QMetaObject::invokeMethod(textEdit, "append", Q_ARG(QString,message));
        QThread::msleep(1);
        // textEdit->setText(message);
    });
    connect(&Task::task, &Task::success,[=](){
        btn_next->setEnabled(true);
    });
}

void InstallPage::showed() {
    installThread = new QThread(this);
    installThread->start();

    Task::task.moveToThread(installThread);
    connect(this, &InstallPage::startInstall,&(Task::task), &Task::install);
    emit startInstall();
}

void InstallPage::updateData() {

}
