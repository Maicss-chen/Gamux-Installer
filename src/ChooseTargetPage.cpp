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
    QVBoxLayout *main_layout = new QVBoxLayout;
    QLabel *tip = new QLabel;
    tip->setText("请避免选择路径中包含非英文、空格、特殊字符等可能影响部分游戏正常运行的字符。");
    tip->setWordWrap(true);
    tip->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    main_layout->addWidget(tip);
    QHBoxLayout *layout = new QHBoxLayout;
    lineEdit->setText(HomeDir() + "/gameux/" + Task::task.config.packageName);
    layout->addWidget(lineEdit);
    layout->addWidget(openChooser);
    main_layout->addLayout(layout);

    connect(openChooser, &QPushButton::clicked, [=](){
        QString dir = QFileDialog::getExistingDirectory(this, "选择安装路径",
                                                        HomeDir(),
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

        if (!dir.isEmpty()) {
            lineEdit->setText(dir+"/"+Task::task.config.packageName);
        }
    });
    mainWidget()->setLayout(main_layout);
    dynamic_cast<QVBoxLayout*>(main_layout)->addStretch();
}


void ChooseTargetPage::showed() {
}

void ChooseTargetPage::updateData() {
    Task::task.setInstallTargetDir(lineEdit->text());
}
