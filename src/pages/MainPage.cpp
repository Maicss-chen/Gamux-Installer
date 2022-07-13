//
// Created by maicss on 22-7-12.
//

#include "MainPage.h"
#include "../Task.h"
#include "utils.h"
#include <unistd.h>
#include <QLayout>
#include <QLabel>
#include <QDir>
#include <QStackedWidget>
#include <sys/stat.h>
#include <QFileDialog>
#include "InstallPage.h"

MainPage::MainPage(QWidget *parent)
    : m_btn_chooseTarget(new GButton("...", this))
    , m_btn_install(new GButton("安装", this))
    , m_cbx_addToDesktop(new QCheckBox("添加至桌面", this))
    , m_cbx_addToLauncher(new QCheckBox("添加至启动器", this))
    , m_cbx_readAndAllow(new QCheckBox("我已阅读并同意", this))
    , m_line_installTarget(new QLineEdit(this))
{
    auto *layout = new QVBoxLayout;

    auto *layout1 = new QHBoxLayout;
    auto *layout2 = new QHBoxLayout;
    auto *layout3 = new QHBoxLayout;

    auto *label1 = new QLabel("安装位置：");

    m_btn_install->setFixedSize(100,30);
    m_btn_chooseTarget->setFixedSize(38,30);
    m_btn_chooseTarget->setBackgroundColor("#112030");
    m_btn_chooseTarget->setRadius(5);
    m_btn_install->setRadius(15);


    layout1->addWidget(label1);
    layout1->addWidget(m_line_installTarget);
    layout1->addWidget(m_btn_chooseTarget);
    layout1->setMargin(0);
    layout1->setSpacing(5);
    layout->addLayout(layout1);

    layout2->addStretch();
    layout2->addWidget(m_cbx_addToLauncher);
    layout2->addWidget(m_cbx_addToDesktop);
    layout2->setMargin(0);
    layout2->setSpacing(12);
    layout->addLayout(layout2);

    layout3->addWidget(m_cbx_readAndAllow);
    layout3->addStretch();
    layout3->addWidget(m_btn_install);
    layout3->setMargin(0);
    layout->addLayout(layout3);

    layout->setSpacing(0);
    layout->setContentsMargins(20, 0, 20, 0);
    setLayout(layout);


    m_line_installTarget->setText(HomeDir() + "/Gamux/" + Task::task.config.packageName);
    m_cbx_addToLauncher->setChecked(true);

    connect(m_btn_install, &GButton::clicked, this, &MainPage::startInstall);
    connect(m_cbx_readAndAllow, &QCheckBox::stateChanged, this, &MainPage::checkPath);
    connect(m_line_installTarget,&QLineEdit::textChanged, this, &MainPage::checkPath);
    connect(m_btn_chooseTarget,&GButton::clicked, [=](){
        QString dir = QFileDialog::getExistingDirectory(this, "选择安装路径",
                                                        HomeDir(),
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
        if (!dir.isEmpty()) {
            m_line_installTarget->setText(dir+"/"+Task::task.config.packageName);
        }
    });

    m_btn_install->setEnabled(false);
    checkPath();
}

void MainPage::startInstall() {
    Task::task.setAddDesktopIcon(m_cbx_addToDesktop->isChecked());
    Task::task.setAddLauncherIcon(m_cbx_addToLauncher->isChecked());
    Task::task.setInstallTargetDir(m_line_installTarget->text());

    auto parentSTK = dynamic_cast<QStackedWidget*>(parent());

    if (parentSTK->currentIndex() != parentSTK->count()-1)
        parentSTK->setCurrentIndex(parentSTK->currentIndex()+1);

    auto newPage = dynamic_cast<InstallPage*>(parentSTK->widget(parentSTK->currentIndex()));
    newPage->showed();
}

void MainPage::checkPath() {
    Task::task.setHeaderTip("");
    QString dir = m_line_installTarget->text();

    QDir qDir(dir);
    if (qDir.exists() && !qDir.isEmpty()){
        Task::task.setHeaderTip("警告：您选择的目录不为空，为了防止数据丢失，通常我们建议您选择一个空目录，若您的确想覆盖安装，可以直接点击安装。");
    }

    QString validPath = getValidParentPath(dir);
    struct stat buf{};
    stat(validPath.toStdString().c_str(),&buf);
    if (!S_ISDIR(buf.st_mode)){
        m_btn_install->setEnabled(false);
        Task::task.setHeaderTip("错误：您选择的必须是一个目录，否则无法安装。");
        return;
    } else {
        m_btn_install->setEnabled(true);
    }

    int res = access(validPath.toStdString().c_str(),W_OK);
    if (res != 0){
        m_btn_install->setEnabled(false);
        Task::task.setHeaderTip("错误：您没有该目录的写入权限，无法安装。");
        return;
    } else {
        m_btn_install->setEnabled(true);
    }
    if (dir.left(4) == "/tmp") {
        Task::task.setHeaderTip("警告：建议您不要将游戏安装在临时目录，否则将在重启后丢失。");
    }
    if (!m_cbx_readAndAllow->isChecked()) {
        m_btn_install->setEnabled(false);
        Task::task.setHeaderTip("清先阅读协议，并勾选“我已阅读并同意”。");
        return;
    }
}
