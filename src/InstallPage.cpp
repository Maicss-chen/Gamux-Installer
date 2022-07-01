//
// Created by maicss on 22-6-24.
//
#include <QApplication>

#include "InstallPage.h"
#include "Task.h"

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
    connect(&Task::task, &Task::updateProgress,[=](int now, int count, QString message){
        progressBar->setMaximum(count);
        progressBar->setValue(now);
        textEdit->append(message);
    });
    connect(&Task::task, &Task::success,[=](){
        btn_next->setEnabled(true);
    });
}

void InstallPage::showed() {
    Task::task.install();
}

void InstallPage::updateData() {

}
