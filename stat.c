
#include <sys/stat.h> // stat(), struct stat

int main() {
    struct stat buffer;
    int status = stat("test.txt", &stat);

    printf("dev_t : %d\n"
           "ino_t : %d\n"
           "mode_t: %d\n"
        buffer.dev_t,
        buffer.ino_t,
        buffer.mode_t,
    );
}
