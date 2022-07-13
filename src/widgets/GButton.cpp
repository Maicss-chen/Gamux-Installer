//
// Created by maicss on 22-7-12.
//

#include "GButton.h"
#include <QPainter>

GButton::GButton(QWidget *parent)
    : m_bgc("#3354FF")
    , m_clickFlag(false) {
    setMinimumSize(100,30);
}

GButton::GButton(const QString &text, QWidget *parent)
    : m_bgc("#3354FF")
    , m_clickFlag(false) {
    setMinimumSize(100,30);

    setText(text);
}

void GButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect(0, 0, QWidget::width(), QWidget::height());
    painter.setPen(nullptr);
    QColor bgc = backgroundColor();
    if (!isEnabled()){
        bgc.setAlpha(100);
    }
    painter.setBrush(bgc);

    painter.drawRoundedRect(rect,m_radius,m_radius);

    painter.setPen("#ffffff");
    painter.drawText(0,0,QWidget::width(),QWidget::height(),Qt::AlignCenter,text());
}

QColor GButton::backgroundColor() {
    return m_bgc;
}

void GButton::setBackgroundColor(QColor color) {
    m_bgc = color;
}

QString GButton::text() {
    return m_text;
}

void GButton::setText(QString text) {
    m_text = text;
}

void GButton::mousePressEvent(QMouseEvent *event) {
    m_clickFlag = true;
}

void GButton::mouseReleaseEvent(QMouseEvent *event) {
    if (m_clickFlag && isEnabled()) {
        emit clicked();
    }
    m_clickFlag = false;
}

void GButton::setRadius(int radius) {
    m_radius = radius;
    update();
}

