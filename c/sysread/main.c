
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_MAX 100

int main() {

    FILE* fileDescriptor;
    char buffer[BUFFER_MAX];

    fileDescriptor = fopen("test.txt","r");

    int count = fread(buffer, 1, BUFFER_MAX, fileDescriptor);
    printf("%s\n", buffer);
    char* filestr = malloc(count+1);
    strcpy(filestr, buffer);

    printf("stacksize: %d    heapsize: %d\n", BUFFER_MAX, strlen(filestr));

    /*    while(1) {
        char c = getc(fileDescriptor);
        if( feof(fileDescriptor) ) {
            break;
        }
        printf("%c", c);
    }*/
    fclose(fileDescriptor);

    free(filestr);
    return 0;
}
