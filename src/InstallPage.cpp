//
// Created by maicss on 22-6-24.
//
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
}

void InstallPage::showed() {
    Task::task.install();
}

void InstallPage::updateData() {

}
