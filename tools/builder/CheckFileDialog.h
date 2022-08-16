//
// Created by maicss on 22-7-16.
//

#ifndef GAMUX_INSTALLER_CHECKFILEDIALOG_H
#define GAMUX_INSTALLER_CHECKFILEDIALOG_H

#include <QDialog>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QNetworkAccessManager>

class CheckFileDialog : public QDialog {
    Q_OBJECT
public:
    explicit CheckFileDialog(QString filename, QString name, QWidget *parent = nullptr);
    /**
     * 调用此对话框选择或下载文件后，可用该接口判断操作是否执行成功。
     * @return 返回是否成功。
     */
    bool isSuccess() const;
private slots:
    void checkFile();
    void updateFile();
    void setMessage(const QString &message);
private:
    QProgressBar *m_progressBar;
    QLabel *m_label;
    QLabel *m_label_2;
    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *networkReply{};
    QTimer *timer;
    qint64 m_speed;
    qint64 m_now{}, m_total{};
    bool m_isSuccess;
    QString m_filename;
    QString m_name;
};


#endif //GAMUX_INSTALLER_CHECKFILEDIALOG_H
