//
// Created by maicss on 22-6-24.
//
#include <QFileDialog>
#include <QDebug>

#include "ChooseTargetPage.h"
#include "utils.h"
#include "../Task.h"

#include <unistd.h>
#include <sys/stat.h>

ChooseTargetPage::ChooseTargetPage(QWidget *parent)
    : Page(parent)
    , lineEdit(new QLineEdit)
    , openChooser(new QPushButton("..."))
    , err_tip(new QLabel)
{

    setTitle("请选择安装目录");
    QVBoxLayout *main_layout = new QVBoxLayout;
    QLabel *tip = new QLabel;
    tip->setText("请避免选择路径中包含非英文、空格、特殊字符等可能影响部分游戏正常运行的字符。");
    tip->setWordWrap(true);
    tip->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    err_tip->setWordWrap(true);
    err_tip->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    main_layout->addWidget(tip);
    QHBoxLayout *layout = new QHBoxLayout;
    lineEdit->setText(HomeDir() + "/Gamux/" + Task::task.config.packageName);
    layout->addWidget(lineEdit);
    layout->addWidget(openChooser);
    main_layout->addLayout(layout);
    main_layout->addWidget(err_tip);

    connect(openChooser, &QPushButton::clicked, [=](){
        QString dir = QFileDialog::getExistingDirectory(this, "选择安装路径",
                                                        HomeDir(),
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

        if (!dir.isEmpty()) {
            lineEdit->setText(dir+"/"+Task::task.config.packageName);
        }
    });
    connect(lineEdit, &QLineEdit::textChanged, this, &ChooseTargetPage::checkPath);
    mainWidget()->setLayout(main_layout);
    dynamic_cast<QVBoxLayout*>(main_layout)->addStretch();

    checkPath();
}


void ChooseTargetPage::showed() {
}

void ChooseTargetPage::updateData() {
    Task::task.setInstallTargetDir(lineEdit->text());
}

void ChooseTargetPage::checkPath() {
    err_tip->setText("");
    QString dir = lineEdit->text();
    QString validPath = getValidParentPath(dir);
    struct stat buf{};
    stat(validPath.toStdString().c_str(),&buf);
    if (!S_ISDIR(buf.st_mode)){
        btn_next->setEnabled(false);
        err_tip->setText("错误：您选择的必须是一个目录，否则无法安装。");
        return;
    } else {
        btn_next->setEnabled(true);
    }

    int res = access(validPath.toStdString().c_str(),W_OK);
    if (res != 0){
        btn_next->setEnabled(false);
        err_tip->setText("错误：您没有该目录的写入权限，无法安装。");
        return;
    } else {
        btn_next->setEnabled(true);
    }
    if (dir.left(4) == "/tmp") {
        err_tip->setText("错误：建议您不要将游戏安装在临时目录，否则将在重启后丢失。");
    }
}
