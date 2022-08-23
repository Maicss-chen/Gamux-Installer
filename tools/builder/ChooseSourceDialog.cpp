//
// Created by maicss on 22-8-16.
//
#include <QFileInfo>
#include "ChooseSourceDialog.h"
#include "ui_ChooseSourceDialog.h"
#include "utils.h"
#include "TarFile.h"

ChooseSourceDialog::ChooseSourceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChooseSourceDialog)
{
    ui->setupUi(this);
    connect(ui->btn_open,  &QPushButton::clicked,[=](){
        QString file = chooseFile("安装器包( *.tar )");
        TarFile tar;
        tar.open(file.toUtf8(), 0);
        QString installerName = "installer_" + QSysInfo::currentCpuArchitecture();
        if (!tar.exists(installerName)){
            MessageBoxExec("错误", "您选择的tar包中没有找到安装器("+installerName+")文件。");
            return;
        }
        if (!file.isEmpty()){
            ui->line_filePath->setText(file);
        }
    });
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(ui->line_filePath, &QLineEdit::textChanged, [=](){
        QFileInfo file(ui->line_filePath->text());
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(file.exists());
    });
    connect(ui->radio_getFromRepo, &QRadioButton::clicked, ui->radio_getFromLocal, &QRadioButton::clicked);
    connect(ui->radio_getFromLocal, &QRadioButton::clicked, [=](){
        ui->line_filePath->setEnabled(!ui->radio_getFromRepo->isChecked());
        ui->btn_open->setEnabled(!ui->radio_getFromRepo->isChecked());
    });
}

ChooseSourceDialog::InstallerType ChooseSourceDialog::getInstallerType() {
    if (ui->radio_getFromRepo->isChecked())
        return ChooseSourceDialog::FROM_REPO;
    else if (ui->radio_getFromLocal->isChecked())
        return ChooseSourceDialog::FROM_LOCAL;
}

QString ChooseSourceDialog::getInstallerPath() {
    return ui->line_filePath->text();
}
