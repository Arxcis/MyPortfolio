#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>                             // @doc select.h - https://linux.die.net/man/2/select
#include <termios.h>                                // @doc termios.h - http://pubs.opengroup.org/onlinepubs/7908799/xsh/termios.h.html

typedef struct {
    struct termios originalTermios;
    fd_set         fileDescriptorSet;
} App;

void initTerminalApp(App* app);
void closeTerminalApp(App* app);
int getch(unsigned char* ch) { return read(0, ch, sizeof(*ch)); }

//
// @function main
// @brief Setting up a non-blocking raw keyboard input loop
// @doc http://stackoverflow.com/questions/448944/c-non-blocking-keyboard-input
//
//int main(int argc, char *argv[])
int main(void)
{
    App app;
    initTerminalApp(&app);

    //
    // @brief keyinput polling loop
    //
    for(;;) {
        // Busy-waiting on input
        int retval;
        while ((retval = !select(1, &app.fileDescriptorSet, NULL, NULL, NULL)));   // @doc select() - http://man7.org/linux/man-pages/man2/select.2.html;

        if (retval == -1) { perror("select()...");}
        ssize_t count;
        unsigned char ch;
        count = getch(&ch);

        printf("%c", ch); /* consume the character */

        if(ch == 'q') break;


        // @doc ESCAPE SEQUENCES arrow codes - http://stackoverflow.com/questions/10463201/getch-and-arrow-codes
        else if (ch == '\027') {
            getch(&ch); // skip the [
            switch(getch(&ch)) { // the real value
                case 'A':
                    printf("ESC[1A"); // code for arrow up

                    break;
                case 'B':
                    printf("ESC[1B"); // code for arrow down

                    break;
                case 'C':
                    printf("ESC[1C"); // code for arrow right

                    break;
                case 'D':
                    printf("ESC[1D"); // code for arrow left
                    break;
                }
        }
    }
    closeTerminalApp(&app);
    return 0;
}


void initTerminalApp(App* app) {
    //
    // @brief configure terminal to raw mode
    //        The old terminal state is cached
    //
    {
        struct termios new_termios;

        tcgetattr(0, &app->originalTermios);              // @doc tcgetattr() - http://pubs.opengroup.org/onlinepubs/7908799/xsh/tcgetattr.html
        memcpy(&new_termios, &app->originalTermios, sizeof(new_termios));

        cfmakeraw(&new_termios);                     //  @doc cfmakeraw() - https://linux.die.net/man/3/cfmakeraw
        tcsetattr(0, TCSANOW, &new_termios);         //  @doc tcsetattr() - http://pubs.opengroup.org/onlinepubs/7908799/xsh/tcsetattr.html
    }

    //
    // @brief set up the file descriptor set
    //
    FD_ZERO(&app->fileDescriptorSet);            // Clears the set
    FD_SET(0, &app->fileDescriptorSet);          // FD 0 is stdin

    //
    // @brief Setting up screen
    //                                        // @doc control sequence table - https://www.gnu.org/software/screen/manual/html_node/Control-Sequences.html
    setbuf(stdout, NULL);                 // @doc setbuf() - http://man7.org/linux/man-pages/man3/setbuf.3.html
    printf("\e[8;30;80t");   // Resize window
    printf("\033c");         // Clear window
}

void closeTerminalApp(App* app) {
    tcsetattr(0, TCSANOW, &app->originalTermios);
    setlinebuf(stdout);
    printf("\033c");
}
