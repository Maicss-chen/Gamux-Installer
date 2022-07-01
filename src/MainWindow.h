//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_MAINWINDOW_H
#define GAMEINSTALLER_MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "pages/ReadMePage.h"
#include "pages/ChooseTargetPage.h"
#include "pages/OptionsPage.h"
#include "pages/InstallPage.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *m_stk;
    ReadMePage *m_readMePage;
    ChooseTargetPage *m_chooseTargetPage;
    OptionsPage *m_optionsPage;
    InstallPage *m_installPage;
};


#endif //GAMEINSTALLER_MAINWINDOW_H
