//
// Created by maicss on 22-7-12.
//

#ifndef GAMUX_INSTALLER_GPROGRESSBAR_H
#define GAMUX_INSTALLER_GPROGRESSBAR_H

#include <QWidget>
#include <QPaintEvent>
class GProgressBar : public QWidget {
    Q_OBJECT
public:
    GProgressBar(QWidget *parent = nullptr);
    void setMaximum(int max);
    void setValue(int value);

private:
    void paintEvent(QPaintEvent *event) override;
    int m_max;
    int m_min;
    int m_value;
};


#endif //GAMUX_INSTALLER_GPROGRESSBAR_H
