#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "board.h"

void play(void);

int main(void)
{
    bool again = true;
    char ans[1] = "n";
    
    while(again){
        play();

        printf("play again? y/n: ");
        scanf("%1s", ans);

        again = (strcmp("y", ans) == 0);
        if(again)
            printf("AGAIN!!!\n\n");
    }

    return 0;
}


void play(void){
    // an array that stores the info whether a place on a board has been checked (dug)
    int dug[BOARD_SIZE*BOARD_SIZE-1];
    for(int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++){
        dug[i] = -1;
    }

    BoardStruct_t board = makeNewBoard();
    assignValuesToBoard(&board);

    BoardStruct_t visibleBoard;
    
    bool safe = true;

    // run until all places on the board has been checked
    while(checkDug(dug)){
        visibleBoard = makeVisibleBoard(&board, dug);
        printVisibleBoard(visibleBoard);
        //printBoard(board);
        
        int userX, userY;
        printf("Input row and then column:\n");
        scanf("%d %d", &userX, &userY);

        if(userX < 0 || userX >= BOARD_SIZE || userY < 0 || userY >= BOARD_SIZE){
            printf("Invalid input!\n");
            continue;
        }

        safe = dig(&board, userX, userY, dug);

        if(!safe){
            // if the player digs a bomb
            break;
        }
    }

    if(safe){
        printf("Congratulations!\n");
    } else {
        printf("Oops! Game over\n");
        
        for(int i = 0; i < sizeof(dug)/sizeof(int); i++){
            dug[i] = 1;
        }
        visibleBoard = makeVisibleBoard(&board, dug);
        printVisibleBoard(visibleBoard);
    }

}
