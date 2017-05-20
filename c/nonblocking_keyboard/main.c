#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>                             // @doc select.h - https://linux.die.net/man/2/select
#include <termios.h>                                // @doc termios.h - http://pubs.opengroup.org/onlinepubs/7908799/xsh/termios.h.html


int getch(unsigned char* ch) { return read(0, ch, sizeof(*ch)); }
//
// @function main
// @brief Setting up a non-blocking raw keyboard input loop
// @doc http://stackoverflow.com/questions/448944/c-non-blocking-keyboard-input
//
int main(int argc, char *argv[])
{
    struct termios original_termios;
    //
    // @brief configure terminal to raw mode
    //        The old terminal state is cached
    {
        struct termios new_termios;

        /* take two copies - one for now, one for later */
        tcgetattr(0, &original_termios);             // @doc tcgetattr() - http://pubs.opengroup.org/onlinepubs/7908799/xsh/tcgetattr.html
        memcpy(&new_termios, &original_termios, sizeof(new_termios));

        /* register cleanup handler, and set the new terminal mode */
        cfmakeraw(&new_termios);                     //  @doc cfmakeraw() - https://linux.die.net/man/3/cfmakeraw
        tcsetattr(0, TCSANOW, &new_termios);         //  @doc tcsetattr() - http://pubs.opengroup.org/onlinepubs/7908799/xsh/tcsetattr.html
    }

    //
    // @brief set up the file descriptor set
    //
    //struct timeval tv = { 0, 100 };      // @doc timeval - http://pubs.opengroup.org/onlinepubs/7908799/xsh/systime.h.html
    fd_set fileDescriptorSet;               // Creates a file descriptor set
    FD_ZERO(&fileDescriptorSet);            // Clears the set
    FD_SET(0, &fileDescriptorSet);          // FD 0 is stdin

    setbuf(stdout, NULL);                 // @doc setbuf() - http://man7.org/linux/man-pages/man3/setbuf.3.html
    printf("\033c");
    //
    // @brief keyinput polling loop
    //
    for(;;) {
        // Busy-waiting on input
        int retval;
        while ((retval = !select(1, &fileDescriptorSet, NULL, NULL, NULL)));   // @doc select() - http://man7.org/linux/man-pages/man2/select.2.html;

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

    tcsetattr(0, TCSANOW, &original_termios);
    setlinebuf(stdout);
    printf("\033c");
    return 0;
}
