#include <stdio.h>
#include <stdlib.h>

#define COLS 30
#define ROWS 15

int main() {
    int quit = 0;
    while (!quit) {
        // render table 
        printf("◤");
        for (int i = 0; i< COLS -1 ; i++) {
            printf(".");
        }
        printf("◥\n");
        for (int j = 0; j<ROWS; j++) {
            printf("|");
            for (int i = 0; i<COLS; i++){
                printf(".");
            }
            printf("|\n");
        }

        printf("◣");
        for (int i = 0; i< COLS - 1; i++) {
            printf(".");
        }
        printf("◢\n");
        
        printf("\e[%iA", ROWS + 2);
    }
    return 0;
}
