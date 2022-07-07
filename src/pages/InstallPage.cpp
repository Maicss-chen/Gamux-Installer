//
// Created by maicss on 22-6-24.
//
#include <QApplication>
#include <QTimer>
#include <QScrollBar>

#include "InstallPage.h"
#include "../Task.h"

InstallPage::InstallPage(QWidget *parent)
    : Page(parent)
    , progressBar(new QProgressBar(this))
    , labelOut(new QLabel(this))
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
    layout->addWidget(labelOut);
    mainWidget()->setLayout(layout);

    labelOut->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    connect(&Task::task, &Task::updateProgress,[=](size_t now, size_t count, const QString& message){
        progressBar->setMaximum(int(count));
        progressBar->setValue(int(now));
        out = message;
    });
    auto *timer = new QTimer;
    timer->setInterval(100);
    connect(timer,&QTimer::timeout,[=](){
        labelOut->setText(out);
    });
    timer->start();

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
