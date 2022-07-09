//
// Created by maicss on 22-7-6.
//


#ifndef GAMUX_INSTALLER_TAR_H
#define GAMUX_INSTALLER_TAR_H


#include <vector>
#include <string>
#include <QObject>
#include "tar.h"
class TarFile : public QObject{
    Q_OBJECT
public:
    explicit TarFile();
    ~TarFile() override;

    /**
     * 打开.sh文件
     * @param tar_name .sh文件的文件名
     * @param startPos tar包数据的起始位置（单位：字节）
     * @return 返回是否打开成功
     */
    bool open(const char* tar_name,unsigned long startPos);
    /**
     * 获取tar文件的节点数量（包括文件、文件夹、链接等）
     * @param filterPath 筛选前缀，只统计名称为指定前缀的节点
     * @return
     */
    size_t getNodeCount(const QString& filterPath="");
    /**
     * 解压文件到指定位置
     * @param target 解压的目标位置（若不存在则自动创建）
     * @param filterPath 筛选前缀，只解压名称为指定前缀的节点，解压时忽略该前缀。
     * 例如：target设为/abc目录，filterPath设置为game/，那么压缩包中的game/bcd.txt文件将被解压到/abc/bcd.txt，
     * 而压缩包中的data/cde.txt将因不满足前缀筛选，不被解压。
     * @return
     */
    bool unpack(const QString& target, const QString& filterPath="");
    /**
     * 读文本文件，从压缩包中以文本形式读取某个文件内容。
     * @param filename 要读取的文件在压缩包中的文件名。
     * @return
     */
    QString readTextFile(const QString& filename);
signals:
    /**
     * 进度信号
     * @param now 正在解析的文件个数
     * @param filename 正在解析的文件名
     */
    void progressReady(size_t now, QString filename);
private:
    FILE* file;
    long offset{};
    long tar_size{};
};
#endif //GAMUX_INSTALLER_TAR_H