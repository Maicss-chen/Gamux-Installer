//
// Created by maicss on 22-7-13.
//

#include "GHeader.h"

GHeader::GHeader(QWidget *parent)
        : QWidget(parent)
{

}

void GHeader::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPen pen;
    pen.setWidth(0);
    pen.setColor(QColor(255,255,255));
    painter.setPen(pen);
    painter.drawPixmap(0,0,QWidget::width(),QWidget::height(),m_pixmap);

    if (!m_tip.isEmpty()) {
        QLinearGradient linearGradient(0,0,0,QWidget::height());
        linearGradient.setColorAt(0,QColor(0,0,0,0));
        linearGradient.setColorAt(1,QColor(0,0,0,240));
//        painter.setBrush(linearGradient);
        painter.fillRect(0,0,QWidget::width(),QWidget::height(),linearGradient);


        painter.drawText(0,QWidget::height()/2,QWidget::width(),QWidget::height()/2,
                         Qt::AlignCenter | Qt::TextWordWrap,m_tip);
    }

    QWidget::paintEvent(event);
}

void GHeader::setText(QString text) {
    m_tip = text;
    update();
}

void GHeader::setPixmap(const QPixmap &pixmap) {
    m_pixmap = pixmap;
    update();
}
