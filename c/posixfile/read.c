
#include <fcntl.h>  // open()
#include <unistd.h>  // read(), close()

#define BUFFER_MAX 100

int main (void) {

    char buffer[100];
    int fileDescriptor = open("test.txt", O_RDONLY);

    read(fileDescriptor, buffer, BUFFER_MAX);
    printf("%s\n", buffer);
    close(fileDescriptor);

    return 0;
}
