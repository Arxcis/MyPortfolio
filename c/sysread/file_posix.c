
#include <fcntl.h>
#include <unistd.h>  // POSIX HEADER

#define BUFFER_MAX 100

int main (void) {

    char buffer[100];
    int fileDescriptor = open("test.txt", O_RDONLY);

    read(fileDescriptor, buffer, BUFFER_MAX);
    printf("%s\n", buffer);
    close(fileDescriptor);

    return 0;
}
