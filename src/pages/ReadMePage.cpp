//
// Created by maicss on 22-6-24.
//
#include <QDebug>
#include <QFile>

#include "ReadMePage.h"
#include "../Task.h"
ReadMePage::ReadMePage(QWidget *parent)
    : Page(parent)
    , textEdit(new QTextEdit)
    , checkBox(new QCheckBox)
{
    QFile readme(Task::task.config.readme);
    readme.open(QFile::ReadOnly);
    textEdit->setText(readme.readAll());
    textEdit->setReadOnly(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textEdit);

    checkBox->setText("我以阅读并同意其中内容");
    layout->addWidget(checkBox);
    mainWidget()->setLayout(layout);
    setTitle("请先阅读");
    btn_next->setEnabled(false);

    connect(checkBox, &QCheckBox::stateChanged, btn_next, &QPushButton::setEnabled);
}

void ReadMePage::showed() {
}

void ReadMePage::updateData() {

}
