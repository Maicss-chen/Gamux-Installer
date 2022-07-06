//
// Created by maicss on 22-7-6.
//

#include "TarFile.h"

#include <cstring>
#include <fstream>
#include <iostream>

#include <QDir>
#include <QDebug>

#include "utils.h"
#include <unistd.h>
#include <sys/stat.h>
using namespace std;

TarFile::TarFile(const char* tar_name)
        : file(nullptr)
{
    file = fopen(tar_name, "rb");
}


TarFile::~TarFile()
{
    if (file) {
        fclose(file);
        file = nullptr;
    }
}

size_t TarFile::getNodeCount() {
    if (!file) return 0;
    const int block_size{ 512 };
    unsigned char buf[block_size];
    auto* header = (tar_posix_header*)buf;
    memset(buf, 0, block_size);

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (size % block_size != 0) {
        fprintf(stderr, "tar file size should be a multiple of 512 bytes: %zu\n", size);
        return 0;
    }

    size_t pos{ 0 };
    size_t res = 0;
    while (true) {
        size_t read_size = fread(buf, block_size, 1, file);
        if (read_size != 1) break;
        if (strncmp(header->magic, TMAGIC, 5) != 0) break;
        res++;
        pos += block_size;
        size_t file_size{0};
        sscanf(header->size, "%lo", &file_size);
        size_t file_block_count = (file_size + block_size - 1) / block_size;
        pos += file_block_count * block_size;
        fseek(file, pos, SEEK_SET);
    }
    fseek(file, 0, SEEK_SET);
    return res;
}

bool TarFile::unpack(const QString& target) {
    if (!file) return false;
    mkdirP(target);
    const int block_size{ 512 };
    unsigned char buf[block_size];
    auto* header = (tar_posix_header*)buf;
    memset(buf, 0, block_size);

    size_t pos{ 0 };
    size_t now = 0;
    while (true) {
        now++;
        emit progressReady(now,header->name);
        size_t read_size = fread(buf, block_size, 1, file);
        if (read_size != 1) break;
        if (strncmp(header->magic, TMAGIC, 5) != 0) break;
        pos += block_size;
        size_t file_size{0};
        sscanf(header->size, "%lo", &file_size);
        size_t file_block_count = (file_size + block_size - 1) / block_size;
        mode_t mode;
        sscanf(header->mode, "%o", &mode);
        FILE *outFile;
        char* content;
        auto targetFilename = target +"/"+ header->name;
        switch (header->typeflag) {
            case REGTYPE: // intentionally dropping through
            case AREGTYPE:
                // normal file
                outFile = fopen(targetFilename.toStdString().c_str() , "w+");
                content = new char[file_size];
                fread(content, file_size,1,file);
                for (int i = 0; i < file_size; ++i) {
                    fputc(content[i],outFile);
                }
                delete content;
                fflush(outFile);
                fclose(outFile);
                chmod(targetFilename.toStdString().c_str(), mode);
                break;
            case LNKTYPE:
                // hard link
                break;
            case SYMTYPE:
                // symbolic link
                symlink(header->linkname,targetFilename.toStdString().c_str());
                break;
            case CHRTYPE:
                // device file/special file
                break;
            case BLKTYPE:
                // block device
                break;
            case DIRTYPE:
                mkdirP(targetFilename);
                // directory
                break;
            case FIFOTYPE:
                // named pipe
                break;
            case CONTTYPE:
                break;
            default:
                break;
        }
        pos += file_block_count * block_size;
        fseek(file, pos, SEEK_SET);
    }
    fseek(file, 0, SEEK_SET);

    return true;
}
