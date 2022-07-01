//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_CHOOSETARGETPAGE_H
#define GAMEINSTALLER_CHOOSETARGETPAGE_H

#include <QLineEdit>

#include "Page.h"

class ChooseTargetPage : public Page{
    Q_OBJECT
public:
    ChooseTargetPage(QWidget *parent = nullptr);
    void showed() override;
    void updateData() override;
private:
    QLineEdit *lineEdit;
    QPushButton *openChooser;
};


#endif //GAMEINSTALLER_CHOOSETARGETPAGE_H
