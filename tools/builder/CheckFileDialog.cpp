//
// Created by maicss on 22-7-16.
//

#include "CheckFileDialog.h"
#include "utils.h"
#include <QLayout>
#include <QNetworkReply>
#include <QDataStream>
#include <QFile>
#include <QTimer>
#include <QApplication>
CheckFileDialog::CheckFileDialog(const QString &filename, const QString &name, QWidget *parent)
    : m_progressBar(new QProgressBar)
    , m_label(new QLabel)
    , m_label_2(new QLabel)
    , networkAccessManager(new QNetworkAccessManager)
    , timer(new QTimer)
    , m_isSuccess(true)
    , m_filename(filename)
    , m_name(name)
{
    QLayout *layout = new QVBoxLayout;
    m_label->setText("正在检查"+m_name);
    layout->addWidget(m_label);
    layout->addWidget(m_label_2);
    layout->addWidget(m_progressBar);
    m_label_2->setAlignment(Qt::AlignRight);
    setLayout(layout);
    resize(500,80);
    checkFile();

    timer->setInterval(1000);
    timer->start();
    connect(timer, &QTimer::timeout, [=](){
        if(networkReply->isRunning()){
            m_label_2->setText(toEasyReadByteSize(m_now)+"/"+ toEasyReadByteSize(m_total) +"("+ toEasyReadByteSize(m_speed) +"/s)");
            m_speed = 0;
        }
    });
    this->exec();
}

void CheckFileDialog::checkFile() {
    QString dataDir = getDataPath();
    mkdirP(dataDir);
    QFile installerFile(dataDir + "/" + m_filename);
    if (installerFile.open(QFile::ReadOnly)) {
        setMessage("检查"+m_name+"更新");
        QString localInstallerMd5 = getMd5(dataDir + "/" + m_filename);
        networkReply = networkAccessManager->get(QNetworkRequest(QString(SERVER_URL) + m_filename + ".md5"));
        connect(networkReply, &QNetworkReply::finished, [=](){
            if (networkReply->error() != QNetworkReply::NoError) {
                MessageBoxExec("错误", m_name+"校验信息下载失败 (错误码："+QString::number(networkReply->error())+")");
                m_isSuccess = false;
                close();
            }
            QString res = networkReply->readAll();
            networkReply->close();
            QString repoInstallerMd5 = res.left(res.length()-1);
            if (localInstallerMd5 != repoInstallerMd5){
                updateFile();
            } else {
                // 已经是和仓库一致的版本
                close();
            }
        });
    } else {
        updateFile();
    }
    installerFile.close();
}

void CheckFileDialog::updateFile() {
    setMessage("正在下载安装器");
    QString dataDir = getDataPath();
    static QFile installerFile(dataDir + "/" + m_filename);
    installerFile.open(QFile::WriteOnly);

    networkReply = networkAccessManager->get(QNetworkRequest(QString(SERVER_URL) + m_filename));

    connect(networkReply, &QNetworkReply::readyRead, [=](){
        QByteArray data = networkReply->readAll();
        m_speed += data.size();
        installerFile.write(data);
    });

    connect(networkReply, &QNetworkReply::downloadProgress, [=](qint64 now, qint64 total){
        m_progressBar->setValue(now);
        m_now = now;
        m_progressBar->setMaximum(total);
        m_total = total;
    });

    connect(networkReply, &QNetworkReply::finished, [=](){
        installerFile.close();

        if (networkReply->error() == QNetworkReply::NoError) {
            setMessage("下载完成");
            close();
        } else {
            MessageBoxExec("错误", m_name+"下载失败 (错误码："+QString::number(networkReply->error())+")");
            m_isSuccess = false;
            close();
        }
    });


}

void CheckFileDialog::setMessage(const QString &message) {
    m_label->setText(message);
}

bool CheckFileDialog::isSuccess() {
    return m_isSuccess;
}
