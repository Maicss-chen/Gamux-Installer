//
// Created by maicss on 22-7-12.
//

#ifndef GAMUX_INSTALLER_GBUTTON_H
#define GAMUX_INSTALLER_GBUTTON_H
#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
class GButton : public QWidget{
    Q_OBJECT
public:
    GButton(QWidget *parent = nullptr);
    GButton(const QString &text, QWidget *parent = nullptr);
    void setBackgroundColor(QColor color);
    QColor backgroundColor();
    void setText(QString text);
    QString text();
    void setRadius(int radius);
signals:
    void clicked();
private:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    QColor m_bgc;
    QString m_text;
    bool m_clickFlag;
    int m_radius;
};


#endif //GAMUX_INSTALLER_GBUTTON_H
