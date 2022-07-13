//
// Created by maicss on 22-6-24.
//
#include "MainWindow.h"
#include "Task.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : GWidget(parent)
    , m_titleBar(new GTitleBar(this))
    , m_stk(new QStackedWidget)
    , m_installPage(new InstallPage(m_stk))
    , m_header(new GHeader())
{
    m_titleBar->setTitle(Task::task.config.name+" ("+Task::task.config.version+") 安装");

    m_header->setFixedHeight(215);
    QPixmap pixmap;
    pixmap.loadFromData(Task::task.config.header);
    m_header->setPixmap(pixmap);
    connect(&Task::task, &Task::headerTipChanged, m_header, &GHeader::setText);
    connect(&Task::task, &Task::headerPixmapChanged, m_header, &GHeader::setPixmap);
    connect(&Task::task, &Task::closeButtonEnableChanged, m_titleBar, &GTitleBar::setCloseButtonEnable);
    m_mainPage = new MainPage(m_stk);

    QLayout *qLayout = new QVBoxLayout;
    qLayout->addWidget(m_titleBar);
    qLayout->addWidget(m_header);
    qLayout->addWidget(m_stk);
    qLayout->setMargin(0);
    qLayout->setSpacing(0);
    m_stk->setStyleSheet("*{color: #fff;}"
                         "QLineEdit {"
                         "  border: none;"
                         "  border-radius: 5px;"
                         "  padding: 5px;"
                         "  background: #112030;"
                         "}"
                         "QCheckBox::indicator {"
                         "  background: #112030;"
                         "  color: #fff;"
                         "  border-radius: 3px;"
                         "}"
                         "QCheckBox::indicator:checked {"
                         "  background: #3354FF;"
                         "}");

    GWidget::setLayout(qLayout);

    QColor shadowColor("#555");
    shadowColor.setAlpha(40);
    windowShadow()->setEnabled(true);
    windowShadow()->setColor(shadowColor);
    windowShadow()->setBlurRadius(32);
    windowShadow()->setOffset(6,6);
    setBackground(QColor("#000C1C"));
    setRadius(5);

    int top_w = windowShadow()->blurRadius()/2 - windowShadow()->offset().y();
    int left_w = windowShadow()->blurRadius()/2- windowShadow()->offset().x();
    int right_w = windowShadow()->blurRadius()/2+ windowShadow()->offset().x();
    int bottom_w = windowShadow()->blurRadius()/2+ windowShadow()->offset().y();

    setPadding(top_w,right_w,bottom_w,left_w);
    setFixedSize(460 + padding().left + padding().right,388 + padding().top + padding().bottom);

    m_stk->addWidget(m_mainPage);
    m_stk->addWidget(m_installPage);
    m_stk->setCurrentIndex(0);
    m_stk->setFixedHeight(147);
}
