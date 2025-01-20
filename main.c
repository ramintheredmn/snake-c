/*******************
* Ramin Rafiee     *
* Snake Game       *
*******************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <termio.h>

#define COLS 32
#define ROWS 16

int main() {
    // hide curser 
    printf("\e[?25l");
    // switch to canonical mode, disable echo
    // the termios struct is defined in the termios.h header
    // its just the correct types for flags that we try to manipulate with masking and unmask
    struct termios oldt, newt;
    // tcgetattr gets the current settings of the terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);


    int quit = 0;
    // keep track of snake pos in x, y 2D screen
    int x[1000], y[1000];
    while (!quit) {
        // render table 
        printf("◤ ");
        for (int i = 0; i< COLS -2 ; i++) {
            printf("▬");
        }
        printf("◥\n");
        for (int j = 0; j<ROWS; j++) {
            printf("▮");
            for (int i = 0; i<COLS; i++){
                printf(".");
            }
            printf("▮\n");
        }

        printf("◣ ");
        for (int i = 0; i< COLS - 2; i++) {
            printf("▬");
        }
        printf("◢\n");
        
        // moves curser to the top 
        printf("\e[%iA", ROWS + 2);
        // initialize head and tail variables
        int head = 0, tail = 0;
        // put the snake at the middle
        x[head] = COLS/2;
        y[head] = ROWS/2;
        
        int gameover = 0;
        int xdir = 1, ydir = 0;
        int applex = -1, appley = 0;

        while (!gameover & !quit) {
            if (applex < 0) {
                // create the new apple
                applex = rand() % COLS;
                appley = rand() % ROWS;
                for (int i = tail; i != head; i = (i + 1) % 1000)
                  if (x[i] == applex && y[i] == appley)
                    applex = -1;



                if (applex > 0) {
                // draw the apple
                printf("\e[%iB\e[%iC🍎", y[appley] + 1, x[applex] + 1);
                printf("\e[%iF", y[appley] + 1);
                }
            }



            // clear snake tail
            // put a dot to the snake tail and move the curser to the snake head
            printf("\e[%iB\e[%iC.", y[tail] + 1, x[tail] + 1);
            printf("\e[%iF", y[tail] +1);

            tail = (tail + 1) % 1000;
            int newhead = (head + 1) % 1000;
            x[newhead] = (x[head] + xdir + COLS) % COLS;
            y[newhead] = (y[head] + ydir + ROWS) % ROWS;

            // draw snake head
            printf("\e[%iB\e[%iC🐍", y[head] + 1, x[head] + 1);
            printf("\e[%iF", y[head] +1);

            usleep(5*1000000 / 60);
            // get user input
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 0;
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(STDIN_FILENO, &fds);

            select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
            if (FD_ISSET(STDIN_FILENO, &fds)) {
                int ch = getchar();

                if (ch == 27 || ch == 'q') {
                  quit = 1;
                } else if (ch == 'h' && xdir != 1) {
                  xdir = -1;
                  ydir = 0;
                } else if (ch == 'l' && xdir != -1) {
                  xdir = 1;
                  ydir = 0;
                } else if (ch == 'j' && ydir != -1) {
                  xdir = 0;
                  ydir = 1;
                } else if (ch == 'k' && ydir != 1) {
                  xdir = 0;
                  ydir = -1;
                }
            }
            if (!quit) {
      // Show game over
            printf("\e[%iB\e[%iC Game Over! ", ROWS / 2, COLS / 2 - 5);
            printf("\e[%iF", ROWS / 2);
            fflush(stdout);
            getchar();
            }
        }
    }
            
    // show curser 
    printf("\e[?25h");
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
