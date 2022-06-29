//
// Created by maicss on 22-6-24.
//

#include "MainWindow.h"
#include "Task.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_stk(new QStackedWidget)
    , m_readMePage(new ReadMePage(m_stk))
    , m_chooseTargetPage(new ChooseTargetPage(m_stk))
    , m_optionsPage(new OptionsPage(m_stk))
    , m_installPage(new InstallPage(m_stk))
{
    setWindowTitle(Task::task.config.name+" ("+Task::task.config.version+")");
    setFixedSize(600,400);

    setCentralWidget(m_stk);
    m_stk->addWidget(m_readMePage);
    m_stk->addWidget(m_chooseTargetPage);
    m_stk->addWidget(m_optionsPage);
    m_stk->addWidget(m_installPage);
    m_stk->setCurrentIndex(0);
}
