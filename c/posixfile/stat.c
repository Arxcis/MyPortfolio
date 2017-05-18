
#include <sys/stat.h> // stat(), struct stat
#include <stdio.h>

int main() {
    struct stat buffer;
    int status = stat("test.txt", &buffer);

    printf("DeviceID  : %d\n"
           "FileSN    : %llu\n"
           "File mode : %d\n"
           "Hardlinks : %d\n"
           "UserID    : %d\n"
           "GroupID   : %d\n"
           "-------------\n"
           "LastAccess: %lu\n"
           "LastModify: %lu\n"
           "LastChange: %lu\n"
           "-------------\n"
           "Filesize   : %llu\n"
           "BlockCount : %llu\n"
           "I/O blksize: %d\n"
           "-------------\n"
           "Statuscode: %d\n",
        buffer.st_dev,
        buffer.st_ino,
        buffer.st_mode,
        buffer.st_nlink,
        buffer.st_uid,
        buffer.st_gid,
        buffer.st_atime,
        buffer.st_mtime,
        buffer.st_ctime,
        buffer.st_size,
        buffer.st_blocks,
        buffer.st_blksize,
        status
    );
}
