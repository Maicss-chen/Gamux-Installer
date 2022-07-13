//
// Created by maicss on 22-7-13.
//

#ifndef GAMUX_INSTALLER_GHEADER_H
#define GAMUX_INSTALLER_GHEADER_H

#include <QWidget>
#include <QPainter>

class GHeader : public QWidget {
    Q_OBJECT
public:
    GHeader(QWidget *parent = nullptr);
public slots:
    void setText(QString text);
    void setPixmap(const QPixmap &pixmap);
private:
    void paintEvent(QPaintEvent *event) override;
private:
    QPixmap m_pixmap;
    QString m_tip;
};


#endif //GAMUX_INSTALLER_GHEADER_H
