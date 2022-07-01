//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_READMEPAGE_H
#define GAMEINSTALLER_READMEPAGE_H
#include <QTextEdit>
#include <QCheckBox>

#include "Page.h"
class ReadMePage : public Page {
    Q_OBJECT
public:
    explicit ReadMePage(QWidget *parent = nullptr);

    void showed() override;
    void updateData() override;
private:
    QTextEdit *textEdit;
    QCheckBox *checkBox;
};


#endif //GAMEINSTALLER_READMEPAGE_H
