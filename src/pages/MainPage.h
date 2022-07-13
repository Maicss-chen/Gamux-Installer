//
// Created by maicss on 22-7-12.
//

#ifndef GAMUX_INSTALLER_MAINPAGE_H
#define GAMUX_INSTALLER_MAINPAGE_H

#include <QWidget>
#include <QLineEdit>
#include "../widgets/GButton.h"
#include <QCheckBox>
#include <QLabel>
class MainPage : public QWidget{
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);
public slots:
    void startInstall();
    void checkPath();
private:
    QLineEdit *m_line_installTarget;
    GButton *m_btn_chooseTarget;
    QCheckBox *m_cbx_addToLauncher;
    QCheckBox *m_cbx_addToDesktop;
    QCheckBox *m_cbx_readAndAllow;
    GButton *m_btn_install;
};


#endif //GAMUX_INSTALLER_MAINPAGE_H
