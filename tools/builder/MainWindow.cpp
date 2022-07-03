//
// Created by maicss on 22-7-3.
//

#include "MainWindow.h"
#include "Task.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->line_outdir->setText(HomeDir());
    connect(ui->btn_start,&QPushButton::clicked,this,&MainWindow::start);
    connect(&task, &Task::updateProgress, [=](int now, int count, QString message){
        ui->progressBar->setValue(now);
        ui->progressBar->setMaximum(count);
        ui->statusbar->showMessage(message);
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::start() {
    Task::Config config;
    config.name = ui->line_name->text();
    config.version = ui->line_version->text();
    config.packageName = ui->line_packagename->text();
    config.desktopFilePath = ui->line_desktopfile->text();
    config.readmeFilePath = ui->line_readmefile->text();
    if (ui->cbx_x86_64->isChecked()){
        config.gameDir.append({"x86_64",ui->line_x86_64->text()});
    }
    if (ui->cbx_aarch64->isChecked()){
        config.gameDir.append({"aarch64",ui->line_aarch64->text()});
    }
    task.setConfig(config);
    task.start();
}
