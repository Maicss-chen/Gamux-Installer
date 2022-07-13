//
// Created by maicss on 22-7-12.
//

#ifndef GAMUX_INSTALLER_GTITLEBAR_H
#define GAMUX_INSTALLER_GTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include "GButton.h"
class GTitleBar : public QWidget{
    Q_OBJECT
public:
    GTitleBar(QWidget *parent = nullptr);

    void setTitle(const QString &title);
public slots:
    void setCloseButtonEnable(bool enable);
private:
    void paintEvent(QPaintEvent *event) override;
private:
    GButton *m_btn_close;
    GButton *m_btn_min;
    QString m_text;
};


#endif //GAMUX_INSTALLER_GTITLEBAR_H
