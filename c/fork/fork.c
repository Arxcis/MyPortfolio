
#include <unistd.h>
#include <stdlib.h>

int main() {

    int pid = fork();
    if (pid) {
        printf("Hello from %d\n", pid);
        exit(0);
    }
    printf("Hello from %d\n", pid);
    return 0;
}

// fork()
// read()
// write()
// pthread()
// close()
