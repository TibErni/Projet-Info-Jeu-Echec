#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define PLAYER1_IS_AI true
#define PLAYER2_IS_AI false
#define MAX_INPUT_LENGTH 50
#define BOARD_SIZE 8 

typedef enum {
    EMPTY,
    PLAYER1,
    PLAYER1_PROMOTED,
    PLAYER2,
    PLAYER2_PROMOTED
} Piece;

typedef Piece Board[BOARD_SIZE][BOARD_SIZE];

typedef int BackgroundBoard[BOARD_SIZE][BOARD_SIZE];

