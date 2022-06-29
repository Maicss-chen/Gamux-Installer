//
// Created by maicss on 22-6-24.
//
#include <QFileDialog>
#include <QDebug>
#include "ChooseTargetPage.h"
#include "utils.h"
#include "Task.h"
ChooseTargetPage::ChooseTargetPage(QWidget *parent)
    : Page(parent)
    , lineEdit(new QLineEdit)
    , openChooser(new QPushButton("..."))
{

    setTitle("请选择安装目录");
    QHBoxLayout *layout = new QHBoxLayout;
    lineEdit->setText(HomeDir() + "/gameux/" + Task::task.config.name); // TODO: 这里的gamename需要从配置文件中读取
    layout->addWidget(lineEdit);
    layout->addWidget(openChooser);


    connect(openChooser, &QPushButton::clicked, [=](){
        QString dir = QFileDialog::getExistingDirectory(this, "选择安装路径",
                                                        HomeDir(),
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

        if (!dir.isEmpty()) {
            lineEdit->setText(dir+"/"+Task::task.config.name);
        }
    });

    mainWidget()->setLayout(layout);
}


void ChooseTargetPage::showed() {
}

void ChooseTargetPage::updateData() {
    Task::task.setInstallTargetDir(lineEdit->text());
}
