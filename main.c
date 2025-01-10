#include <stdio.h>
#include <stdlib.h>

#define COLS 32
#define ROWS 16

int main() {
    // hide curser 
    printf("\e[?25l");
    int quit = 0;
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
        
        printf("\e[%iA", ROWS + 2);
        int head = 0, tail = 0;
        x[head] = COLS/2;
        y[head] = ROWS/2;
        
        int gameover = 0;
        int xdir = 1, ydir = 0;

        while (!gameover & !quit) {
            // clear snake tail
            printf("\e[%iB\e[%iC.", y[tail] + 1, x[tail] + 1);
            printf("\e[%iF", y[tail] +1);

            tail = (tail + 1) % 1000;
            int newhaed = (head + 1) % 1000;
            x[newhaed] = (x[head] + xdir + COLS) % COLS;
            y[newhead] = (y[head] + ydir + ROWS) % ROWS;

            // draw snake head
            printf("\e[%iB\e[%iC🐍", y[head] + 1, x[head] + 1);
            printf("\e[%iF", y[head] +1);

        }
    }
    // show curser 
    printf("\e[?25h");

    return 0;
}
