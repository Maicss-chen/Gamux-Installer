//
// Created by maicss on 22-6-24.
//

#include "OptionsPage.h"
#include "../Task.h"
OptionsPage::OptionsPage(QWidget *parent)
    : Page(parent)
    , option_desktop_icon(new QCheckBox("添加桌面图标"))
    , option_launcher_icon(new QCheckBox("添加启动器图标"))
{
    setTitle("安装选项");
    btn_next->setText("安装");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(option_desktop_icon);
    layout->addWidget(option_launcher_icon);
    layout->addStretch();
    mainWidget()->setLayout(layout);
    option_launcher_icon->setCheckState(Qt::CheckState::Checked);

}

void OptionsPage::showed() {

}

void OptionsPage::updateData() {
    Task::task.setAddDesktopIcon(option_desktop_icon);
    Task::task.serAddLauncherIcon(option_launcher_icon);
}
