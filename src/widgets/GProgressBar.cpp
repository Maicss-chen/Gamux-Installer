//
// Created by maicss on 22-7-12.
//

#include "GProgressBar.h"
#include <QPainter>
#include <QDebug>

GProgressBar::GProgressBar(QWidget *parent)
    : QWidget(parent)
    , m_min(0)
    , m_max(100)
    , m_value(0)
{
    setValue(50);
}

void GProgressBar::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect(0, 0, QWidget::width(), QWidget::height());
    painter.setPen(QColor(0,0,0,0));
    painter.setBrush(QColor(255,255,255,20));
    painter.drawRoundedRect(rect,QWidget::height()/2,QWidget::height()/2);

    int w = QWidget::width()*(m_value-m_min)/(m_max-m_min);


    QLinearGradient linearGradient(0,0,w,0);
    linearGradient.setColorAt(0,"#11101f");
    linearGradient.setColorAt(1,"#3354FF");
    painter.setBrush(linearGradient);

    rect.setWidth(w);
    painter.drawRoundedRect(rect,QWidget::height()/2,QWidget::height()/2);

    setFixedHeight(10);

}

void GProgressBar::setMaximum(int max) {
    m_max = max;
}

void GProgressBar::setValue(int value) {
    m_value = value;
    update();
}
