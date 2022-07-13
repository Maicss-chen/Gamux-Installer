//
// Created by maicss on 22-7-12.
//

#include "GTitleBar.h"
#include <QLayout>
#include <QApplication>
#include <QPainter>

GTitleBar::GTitleBar(QWidget *parent)
    : QWidget(parent)
    , m_btn_close(new GButton)
    , m_btn_min(new GButton)
{
    m_btn_close->setBackgroundColor("#FF3C3C");
    m_btn_min->setBackgroundColor("#FFE03C");
    m_btn_min->setFixedSize(18,18);
    m_btn_close->setFixedSize(18,18);
    m_btn_close->setRadius(9);
    m_btn_min->setRadius(9);

    auto *layout = new QHBoxLayout;
    layout->addStretch();
    layout->addWidget(m_btn_min);
    layout->addWidget(m_btn_close);
    layout->setMargin(8);
    layout->setAlignment(Qt::AlignVCenter);

    setLayout(layout);
    setFixedHeight(26);

    connect(m_btn_close, &GButton::clicked, [=](){
       QApplication::exit(0);
    });
    connect(m_btn_min, &GButton::clicked, [=](){
        parent->showMinimized();
    });
}

void GTitleBar::setTitle(const QString &title) {
    m_text = title;
}

void GTitleBar::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen("#ffffff");
    painter.drawText(0,0,QWidget::width(),QWidget::height(),Qt::AlignCenter,m_text);
}

void GTitleBar::setCloseButtonEnable(bool enable) {
    m_btn_close->setEnabled(enable);
}
