//
// Created by maicss on 22-7-3.
//

#ifndef GAMUX_INSTALLER_MAINWINDOW_H
#define GAMUX_INSTALLER_MAINWINDOW_H

#include <QMainWindow>
#include "Task.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent= nullptr);
    ~MainWindow();
public slots:
    void start();
private:
    Ui::MainWindow *ui;
    Task task;
};


#endif //GAMUX_INSTALLER_MAINWINDOW_H
