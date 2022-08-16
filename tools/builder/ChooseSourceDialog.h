//
// Created by maicss on 22-8-16.
//

#ifndef GAMUX_INSTALLER_CHOOSESOURCEDIALOG_H
#define GAMUX_INSTALLER_CHOOSESOURCEDIALOG_H
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ChooseSourceDialog; }
QT_END_NAMESPACE

class ChooseSourceDialog : public QDialog {
    Q_OBJECT

public:
    enum InstallerType {
        FROM_REPO,
        FROM_LOCAL
    };
    explicit ChooseSourceDialog(QWidget *parent= nullptr);
    InstallerType getInstallerType();
    QString getInstallerPath();
private:
    Ui::ChooseSourceDialog *ui;
};


#endif //GAMUX_INSTALLER_CHOOSESOURCEDIALOG_H
