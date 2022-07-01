//
// Created by maicss on 22-6-24.
//
#ifndef GAMEINSTALLER_OPTIONSPAGE_H
#define GAMEINSTALLER_OPTIONSPAGE_H

#include <QCheckBox>

#include "Page.h"

class OptionsPage : public Page{
    Q_OBJECT
public:
    explicit OptionsPage(QWidget *parent);
private:
    void showed() override;
    void updateData() override;
    QCheckBox *option_desktop_icon;
    QCheckBox *option_launcher_icon;
};


#endif //GAMEINSTALLER_OPTIONSPAGE_H
