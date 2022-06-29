//
// Created by maicss on 22-6-24.
//

#include "Page.h"
#include <QLayout>
#include <QDebug>
Page::Page(QWidget *parent)
    : QWidget(parent)
    , btn_last(new QPushButton("返回"))
    , btn_next(new QPushButton("下一步"))
    , layout(new QVBoxLayout)
    , main_widget(new QWidget)
    , btn_layout(new QHBoxLayout)
    , m_title(new QLabel)
{
    setLayout(layout);

    layout->addWidget(m_title);
    layout->addWidget(main_widget);
    layout->addLayout(btn_layout);
    btn_layout->addStretch();
    btn_layout->addWidget(btn_last);
    btn_layout->addWidget(btn_next);
    btn_layout->setContentsMargins(16,0,16,10);

    m_title->setFixedHeight(30);
    QFont font_title;
    font_title.setPixelSize(24);
    m_title->setFont(font_title);
    m_title->setContentsMargins(10, 0, 0, 0);

    connect(btn_last, &QPushButton::clicked, this, &Page::lastStep);
    connect(btn_next, &QPushButton::clicked, this, &Page::nextStep);
    updateButtonStatus();
}

void Page::lastStep() {
    if (getParentStackedWidget()->currentIndex() != 0)
        getParentStackedWidget()->setCurrentIndex(getParentStackedWidget()->currentIndex()-1);
    updateButtonStatus();
    auto newPage = dynamic_cast<Page*>(getParentStackedWidget()->widget(getParentStackedWidget()->currentIndex()));
    newPage->showed();
    newPage->updateButtonStatus();
}

QStackedWidget *Page::getParentStackedWidget() {
    return dynamic_cast<QStackedWidget*>(parent());
}

void Page::nextStep() {
    updateData();
    if (getParentStackedWidget()->currentIndex() != getParentStackedWidget()->count()-1)
        getParentStackedWidget()->setCurrentIndex(getParentStackedWidget()->currentIndex()+1);
    updateButtonStatus();
    auto newPage = dynamic_cast<Page*>(getParentStackedWidget()->widget(getParentStackedWidget()->currentIndex()));
    newPage->showed();
    newPage->updateButtonStatus();
}

void Page::updateButtonStatus() {
    if (getParentStackedWidget()->currentIndex() <= 0){
        btn_last->hide();
    } else {
        btn_last->show();
    }
}

QWidget *Page::mainWidget() {
    return main_widget;
}

void Page::setTitle(QString title) {
    m_title->setText(title);
}

