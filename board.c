#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "helpers.h"



BoardStruct_t makeNewBoard(void){
    srand(time(NULL));

    BoardStruct_t board;
    
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            board.arr[i][j] = 0;
        }
    }

    int bombsPlanted = 0;
    
    while(bombsPlanted < NUM_BOMBS){
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;

        // A bomb is represented as 42 - a * in ASCII
        if(board.arr[x][y] == 42){
            continue;
        }

        board.arr[x][y] = 42;
        bombsPlanted++;
    }
        return board;
}

BoardStruct_t makeVisibleBoard(BoardStruct_t* board, int dug[]){
    //Create the board that is being displayed to the player

    BoardStruct_t visibleBoard;

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            visibleBoard.arr[i][j] = 0;
        }
    }

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(dug[BOARD_SIZE*i + j] == 1)
                visibleBoard.arr[i][j] = board->arr[i][j];
            
            else
                visibleBoard.arr[i][j] = 32; //32 represents an empty space in ASCII
        }
    }
    return visibleBoard;
}


void printVisibleBoard(BoardStruct_t board){
    // print the board to the player
    
    printf("   0 1 2 3 4 5 6 7 8 9\n");
    printf("---------------------\n");
    for(int i = 0; i < BOARD_SIZE; i++){
        printf("%d| ", i);
        for(int j = 0; j < BOARD_SIZE; j++){
            if(board.arr[i][j] != 42 && board.arr[i][j] != 32)
                // if a bomb place or unchecked space print it as an ASCII character. Else print the number of neighboring bombs.
                printf("%d ", (board.arr[i][j]));
            else
                printf("%c ", (char)(board.arr[i][j]));
        }
        printf("|\n");
    }
    printf("---------------------\n");
}

void printBoard(BoardStruct_t board){
    // print raw board. for debug purposes or so

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            printf("%d ", board.arr[i][j]);
        }
        printf("\n");
    }
}

void assignValuesToBoard(BoardStruct_t * board){
     //assign each bombless place on the board the number of neighboring bombs

    for(int r = 0; r < BOARD_SIZE; r++){
        for(int c = 0; c < BOARD_SIZE; c++){
            if(board->arr[r][c] == 42){
                continue;
            }
            board->arr[r][c] = getNumberOfNeighboringBombs(*board, r,c);
        }
    }
}


int getNumberOfNeighboringBombs(BoardStruct_t board, int row, int col){
    //calculate the number of neighboring bombs
    int bombCount = 0;

    for(int x = max(0, row -1); x < (min(BOARD_SIZE - 1, row + 1) + 1); x++){
        for(int y = max(0, col - 1); y < (min(BOARD_SIZE -1, col + 1) + 1); y++){
            
            if(x == row && y == col){
                continue;
            }
                
            
            if(board.arr[x][y] == 42){
                bombCount++;
            }
        }
    }
    return bombCount;
}

bool dig(BoardStruct_t * board, int row, int col, int dug[]){
    // check if the place is bombless or no. If bombless and any neighboring also bombless, dig recursively. 
    // return true if no bomb or false if bomb

    dug[row*BOARD_SIZE + col] = 1;

    if(board->arr[row][col] == 42){
        return false;
    }
        

    if(board->arr[row][col] > 0){
        return true;
    }

    for(int x = max(0, row -1 ); x < (min(BOARD_SIZE - 1, row + 1) + 1); x++){
        for(int y = max(0, col - 1); y < (min(BOARD_SIZE -1, col + 1) + 1); y++){

            if(dug[x*BOARD_SIZE+y] == 1)
                continue;
            dig(board, x, y, dug);
        }
    }
    return true;
}

bool checkDug(int dug[]){
    for(int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++){
        if(dug[i] == -1){
            return true;
        }
    }
    return false;
}