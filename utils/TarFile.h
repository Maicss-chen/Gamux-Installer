//
// Created by maicss on 22-7-6.
//


#ifndef GAMUX_INSTALLER_TAR_H
#define GAMUX_INSTALLER_TAR_H


#include <vector>
#include <string>

#include <QObject>
/* tar Header Block, from POSIX 1003.1-1990.  */

/* POSIX header.  */
typedef struct posix_header
{                                     /* byte offset */
    char name[100];               /*   0 */
    char mode[8];                 /* 100 */
    char uid[8];                  /* 108 */
    char gid[8];                  /* 116 */
    char size[12];                /* 124 */
    char mtime[12];               /* 136 */
    char chksum[8];               /* 148 */
    char typeflag;                /* 156 */
    char linkname[100];           /* 157 */
    char magic[6];                /* 257 */
    char version[2];              /* 263 */
    char uname[32];               /* 265 */
    char gname[32];               /* 297 */
    char devmajor[8];             /* 329 */
    char devminor[8];             /* 337 */
    char prefix[155];             /* 345 */
    /* 500 */
} tar_posix_header;

/*
	location  size  field
	0         100   File name
	100       8     File mode
	108       8     Owner's numeric user ID
	116       8     Group's numeric user ID
	124       12    File size in bytes
	136       12    Last modification time in numeric Unix time format
	148       8     Checksum for header block
	156       1     Link indicator (file type)
	157       100   Name of linked file
*/

#define TMAGIC   "ustar"        /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2

/* Values used in typeflag field.  */
#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */

class TarFile : public QObject{
    Q_OBJECT
public:
    explicit TarFile(const char* tar_name);
    ~TarFile();
    size_t getNodeCount();
    bool unpack(const QString& target);
signals:
    void progressReady(size_t now, QString filename);
private:
    FILE* file;
};
#endif //GAMUX_INSTALLER_TAR_H