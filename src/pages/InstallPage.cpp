//
// Created by maicss on 22-6-24.
//
#include <QApplication>
#include <QTimer>
#include <QScrollBar>
#include <QLayout>

#include "InstallPage.h"
#include "../Task.h"

InstallPage::InstallPage(QWidget *parent)
    : QWidget(parent)
    , progressBar(new GProgressBar(this))
    , label_tip(new QLabel(this))
    , installThread(new QThread(this))
    , btn_finish(new GButton("完成",this))
    , m_count(1)
    , m_now(0)
{
    auto *layout = new QVBoxLayout;

    layout->addWidget(label_tip);
    layout->addWidget(progressBar);
//    progressBar->show();

    auto *layout1 = new QHBoxLayout;
    layout1->addStretch();
    layout1->addWidget(btn_finish);
    layout->addLayout(layout1);

    layout->setMargin(20);
    layout->setSpacing(20);
    setLayout(layout);

    btn_finish->setFixedSize(100,30);
    btn_finish->setEnabled(false);

    label_tip->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    label_tip->setWordWrap(true);

    connect(&Task::task, &Task::updateProgress,[=](size_t now, size_t count, const QString& message){
        m_count = count;
        m_now = now;
        out = message;
    });
    auto *timer = new QTimer;
    timer->setInterval(100);
    connect(timer,&QTimer::timeout,[=](){
        progressBar->setMaximum(1000);
        progressBar->setValue(m_now*1000/m_count);
        label_tip->setText("正在安装：（"+QString::number(m_now*100/m_count)+"%）");
    });
    timer->start();

    connect(&Task::task, &Task::success,[=](){
        btn_finish->setEnabled(true);
        Task::task.setCloseButtonEnable(true);
    });

    connect(btn_finish, &GButton::clicked, [=](){
        QApplication::exit(0);
    });
}

void InstallPage::showed() {
    Task::task.setCloseButtonEnable(false);
    installThread = new QThread(this);
    installThread->start();

    Task::task.moveToThread(installThread);
    connect(this, &InstallPage::startInstall,&(Task::task), &Task::install);
    emit startInstall();
}

