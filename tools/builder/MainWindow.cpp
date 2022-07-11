//
// Created by maicss on 22-7-3.
//

#include "MainWindow.h"
#include "Task.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->line_outdir->setText(HomeDir());

    setWindowTitle("Gamux打包器(版本："+QString(VERSION)+")");

    connect(ui->btn_start,&QPushButton::clicked,this,&MainWindow::start);
    connect(&task, &Task::updateProgress, [=](int now, int count, QString message){
        ui->progressBar->setValue(now);
        ui->progressBar->setMaximum(count);
        ui->statusbar->showMessage(message);
    });

    connect(ui->btn_open_x86_64,  &QPushButton::clicked,[=](){
        QString dir = chooseDirectory();
        if (!dir.isEmpty()){
            ui->line_x86_64->setText(dir);
        }
    });
    connect(ui->btn_open_aarch64,  &QPushButton::clicked,[=](){
        QString dir = chooseDirectory();
        if (!dir.isEmpty()){
            ui->line_aarch64->setText(dir);
        }
    });
    connect(ui->btn_open_installer_x86_64,  &QPushButton::clicked,[=](){
        QString file = chooseFile("");
        if (!file.isEmpty()){
            ui->line_installer_x86_64->setText(file);
        }
    });
    connect(ui->btn_open_installer_aarch64,  &QPushButton::clicked,[=](){
        QString file = chooseFile("");
        if (!file.isEmpty()){
            ui->line_installer_aarch64->setText(file);
        }
    });
    connect(ui->btn_open_desktopfile,  &QPushButton::clicked,[=](){
        QString file = chooseFile("快捷方式(*.desktop)");
        if (!file.isEmpty()){
            ui->line_desktopfile->setText(file);
        }
    });
    connect(ui->btn_open_readmefile,  &QPushButton::clicked,[=](){
        QString file = chooseFile("文本文件(*.txt)");
        if (!file.isEmpty()){
            ui->line_readmefile->setText(file);
        }
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::start() {
    if (!check()){
        return;
    }
    Task::Config config;
    config.name = ui->line_name->text();
    config.version = ui->line_version->text();
    config.packageName = ui->line_packagename->text();
    config.desktopFilePath = ui->line_desktopfile->text();
    config.readmeFilePath = ui->line_readmefile->text();
    config.installer_x86_64 = ui->line_installer_x86_64->text();
    config.installer_aarch64 = ui->line_installer_aarch64->text();
    config.outDir = ui->line_outdir->text();
    if (ui->cbx_x86_64->isChecked()){
        config.gameDir.append({"x86_64",ui->line_x86_64->text()});
    }
    if (ui->cbx_aarch64->isChecked()){
        config.gameDir.append({"aarch64",ui->line_aarch64->text()});
    }
    task.setConfig(config);
    task.start();
}

bool MainWindow::check() {
    if (ui->cbx_x86_64->isChecked()){
        if (ui->line_x86_64->text().isEmpty()) {
            MessageBoxExec("警告","请选择x86_64架构的游戏资源文件夹！");
            return false;
        }
        if (ui->line_installer_x86_64->text().isEmpty()) {
            MessageBoxExec("警告","请选择x86_64架构的游戏安装器文件！");
            return false;
        }
    }

    if (ui->cbx_aarch64->isChecked()){
        if (ui->line_aarch64->text().isEmpty()) {
            MessageBoxExec("警告","请选择aarch64架构的游戏资源文件夹！");
            return false;
        }
        if (ui->line_installer_aarch64->text().isEmpty()) {
            MessageBoxExec("警告","请选择aarch64架构的游戏安装器文件！");
            return false;
        }
    }
    if (ui->line_name->text().isEmpty()){
        MessageBoxExec("警告","游戏名称不能为空");
        return false;
    }
    if (ui->line_version->text().isEmpty()){
        MessageBoxExec("警告","游戏版本不能为空");
        return false;
    }
    if (ui->line_packagename->text().isEmpty()){
        MessageBoxExec("警告","包名不能为空");
        return false;
    }
    if (ui->line_desktopfile->text().isEmpty()){
        MessageBoxExec("警告","请选择desktop文件");
        return false;
    }
    if (ui->line_readmefile->text().isEmpty()){
        MessageBoxExec("警告","请选择readme文件");
        return false;
    }
    if (ui->line_outdir->text().isEmpty()) {
        MessageBoxExec("警告", "请选择输出文件夹");
        return false;
    }
    return true;
}
