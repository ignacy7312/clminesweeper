#include <stdio.h>
#include <stdbool.h>
#include "board.h"

int main(void)
{
    int dug[BOARD_SIZE*BOARD_SIZE-1];
    for(int i = 0; i < sizeof(dug)/sizeof(int); i++){
        dug[i] = -1;
    }

    BoardStruct_t board = makeNewBoard();
    assignValuesToBoard(&board);

    BoardStruct_t visibleBoard;
    
    bool safe = true;

    while(checkDug(dug)){
        visibleBoard = makeVisibleBoard(&board, dug);
        printVisibleBoard(visibleBoard);
        //printBoard(board);
        
        int userX, userY;
        printf("podaj row i col:\n");
        scanf("%d %d", &userX, &userY);

        if(userX < 0 || userX >= BOARD_SIZE || userY < 0 || userY >= BOARD_SIZE){
            printf("Invalid input!");
            continue;
        }

        safe = dig(&board, userX, userY, dug);

        if(!safe){
            break;
        }
    }

    if(safe){
        printf("Congratulations!\n");
    } else {
        printf("sorry game over\n");
        
        for(int i = 0; i < sizeof(dug)/sizeof(int); i++){
            dug[i] = 1;
        }
        visibleBoard = makeVisibleBoard(&board, dug);
        printVisibleBoard(visibleBoard);
    }

    return 0;
}


