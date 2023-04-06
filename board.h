#pragma once
#include <stdbool.h>

#define BOARD_SIZE 10
#define NUM_BOMBS 10

typedef struct {
    int arr[BOARD_SIZE][BOARD_SIZE];
} BoardStruct_t;


BoardStruct_t makeNewBoard(void);
void assignValuesToBoard(BoardStruct_t *);
int getNumberOfNeighboringBombs(BoardStruct_t, int, int);
bool dig(BoardStruct_t *, int, int, int *);
void printBoard(BoardStruct_t);
BoardStruct_t makeVisibleBoard(BoardStruct_t* board, int *);
void printVisibleBoard(BoardStruct_t board);
bool checkDug(int *);