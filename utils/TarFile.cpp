//
// Created by maicss on 22-7-6.
//

#include "TarFile.h"

#include <cstring>
#include <iostream>

#include <QDebug>

#include "utils.h"
#include <unistd.h>
#include <sys/stat.h>
using namespace std;

TarFile::TarFile() : file(nullptr)
{
}
bool TarFile::open(const char *tar_name, unsigned long startPos) {
    this->offset=startPos;
    file = fopen(tar_name, "rb");
    return file;
}

TarFile::~TarFile()
{
    if (file) {
        fclose(file);
        file = nullptr;
    }
}

size_t TarFile::getNodeCount(const QString& filterPath) {
    if (!file) return 0;
    const int block_size{ 512 };
    unsigned char buf[block_size];
    auto* header = (posix_header*)buf;
    memset(buf, 0, block_size);

    if (tar_size % block_size != 0) {
        fprintf(stderr, "tar file size should be a multiple of 512 bytes: %zu\n", offset);
        return 0;
    }

    size_t pos{ unsigned (offset) };
    size_t res = 0;
    fseek(file, offset, SEEK_SET);
    while (true) {
        size_t read_size = fread(buf, block_size, 1, file);
        if (read_size != 1) break;
        if (strncmp(header->magic, TMAGIC, 5) != 0) break;
        pos += block_size;
        size_t file_size{0};
        sscanf(header->size, "%lo", &file_size);
        size_t file_block_count = (file_size + block_size - 1) / block_size;
        if (header->typeflag == REGTYPE || header->typeflag == AREGTYPE){
            if (QString(header->name).left(filterPath.length()) == filterPath){
                res++;
            }
        }
        pos += file_block_count * block_size;
        fseek(file, pos, SEEK_SET);
    }
    fseek(file, offset, SEEK_SET);
    return res;
}

bool TarFile::unpack(const QString& target, const QString& filterPath) {
    if (!file) return false;
    mkdirP(target);
    const int block_size{ 512 };
    unsigned char buf[block_size];
    auto* header = (posix_header*)buf;
    memset(buf, 0, block_size);
    char longFilename[PATH_MAX];
    char targetfn[PATH_MAX];

    size_t pos{ unsigned (offset) };
    size_t now = 0;
    fseek(file, offset, SEEK_SET);
    while (true) {
        char filename[100];
        char prefix[155];
        size_t file_size{0};
        mode_t mode;

        size_t read_size = fread(buf, block_size, 1, file);
        if (read_size != 1) break;
        if (strncmp(header->magic, TMAGIC, 5) != 0) break;
        pos += block_size;

        sscanf(header->size, "%lo", &file_size);
        size_t file_block_count = (file_size + block_size - 1) / block_size;
        sscanf(header->mode, "%o", &mode);
        memcpy(filename, header->name, 100);
        memcpy(prefix, header->prefix,155);
        memset(targetfn, 0, PATH_MAX);
        strcpy(targetfn,target.toStdString().c_str());
        strcat(targetfn,"/");

        QString fname;
        if (longFilename[0] != 0) {
            fname = longFilename;
            strcat(targetfn,&longFilename[filterPath.length()]);
            memset(longFilename, 0, PATH_MAX);
        } else {
            fname = QString(prefix) + QString(filename);
            char name[PATH_MAX];
            memset(name,0,PATH_MAX);
            strcat(name,prefix);
            strcat(name,filename);
            strcat(targetfn,&name[filterPath.length()]);
        }

        FILE *outFile;
        char* content;
        switch (header->typeflag) {
            case REGTYPE: // intentionally dropping through
            case AREGTYPE:
                if (fname.left(filterPath.length()) != filterPath) break;
                // normal file
                now++;
                // 发射信号，传递进度信息
                emit progressReady(now,targetfn);
                outFile = fopen(targetfn , "w");
                if (outFile == nullptr) {
                    qDebug()<<targetfn;
                    qDebug()<<filterPath;
                    break;
                }
                content = new char[file_size];
                fread(content, file_size,1,file);
                fwrite(content,file_size,1,outFile);
                delete content;
                fflush(outFile);
                fclose(outFile);
                chmod(targetfn, mode);
                break;
            case SYMTYPE:
                // symbolic link
                if (fname.left(filterPath.length()) != filterPath) break;
                symlink(header->linkname,targetfn);
                break;
            case DIRTYPE:
                if (fname.left(filterPath.length()) != filterPath) break;
                mkdirP(targetfn);
                // directory
                break;
            case GNUTYPE_LONGNAME:
                fread(longFilename, file_block_count * block_size,1,file);
                break;
            default:
                qDebug()<<targetfn << header->typeflag;
                break;
        }
        pos += file_block_count * block_size;
        fseek(file, pos, SEEK_SET);
    }

    fseek(file, offset, SEEK_SET);
    return true;
}
QByteArray TarFile::readFile(const QString& filename) {
    if (!file) return "";
    const int block_size{ 512 };
    unsigned char buf[block_size];
    auto* header = (posix_header*)buf;
    memset(buf, 0, block_size);

    size_t pos{ unsigned (offset) };
    fseek(file, offset, SEEK_SET);
    while (true) {
        size_t read_size = fread(buf, block_size, 1, file);
        if (read_size != 1) break;
        if (strncmp(header->magic, TMAGIC, 5) != 0) break;
        pos += block_size;
        size_t file_size{0};
        sscanf(header->size, "%lo", &file_size);
        size_t file_block_count = (file_size + block_size - 1) / block_size;
        char* content;
        switch (header->typeflag) {
            case REGTYPE: // intentionally dropping through
            case AREGTYPE:
                if (filename==header->name){
                    content = new char[file_size];
                    fread(content, file_size,1,file);
                    fseek(file, offset, SEEK_SET);
                    return QByteArray::fromRawData(content,file_size);
                }
            default:
                break;
        }
        pos += file_block_count * block_size;
        fseek(file, pos, SEEK_SET);
    }
    fseek(file, offset, SEEK_SET);

    return "";
}

bool TarFile::exists(const QString& filename){
    return readFile(filename) != "";
}