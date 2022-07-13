//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_MAINWINDOW_H
#define GAMEINSTALLER_MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "pages/InstallPage.h"
#include "widgets/GWidget.h"
#include "widgets/GTitleBar.h"
#include "widgets/GButton.h"
#include "pages/MainPage.h"
#include "widgets/GHeader.h"

class MainWindow : public GWidget{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *m_stk;
    InstallPage *m_installPage;
    GTitleBar *m_titleBar;
    MainPage *m_mainPage;
    GHeader *m_header;
};


#endif //GAMEINSTALLER_MAINWINDOW_H
