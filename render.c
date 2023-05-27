#include "render.h"

const char* ANSI_COLORS[] = {
    "\x1b[30m",       // Noir
    "\x1b[41m",       // Fond Rouge
    "\x1b[42m",       // Fond Vert
    "\x1b[43m",       // Fond Jaune
    "\x1b[44m",       // Fond Bleu
    "\x1b[45m",       // Fond Magenta
    "\x1b[46m",       // Fond Cyan
    "\x1b[47m",       // Fond Blanc
    "\x1b[100m",      // Fond Gris
    "\x1b[101m",      // Fond Rouge Clair
};

const int NUM_COLORS = sizeof(ANSI_COLORS) / sizeof(ANSI_COLORS[0]);
const char* ANSI_RESET = "\x1b[0m";

void initialize_board(Board board, Piece player1_promoted, Piece player2_promoted)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (i == 0)
            {
                if (j == player1_promoted)
                {
                    board[i][j] = PLAYER1_PROMOTED;
                }
                else
                {
                    board[i][j] = PLAYER1;
                }
            }
            else if (i == BOARD_SIZE - 1)
            {
                if (j == player2_promoted)
                {
                    board[i][j] = PLAYER2_PROMOTED;
                }
                else
                {
                    board[i][j] = PLAYER2;
                }
            }
            else
            {
                board[i][j] = EMPTY;
            }
        }
    }
}

int get_color_index(int x, int y)
{
    return (x + y) % NUM_COLORS;
}

void print_board(const Board board)
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            int color_index = get_color_index(x, y);
            printf("%s", ANSI_COLORS[color_index]);

            if (board[x][y] == EMPTY)
            {
                printf("   ");
            }
            else if (board[x][y] == PLAYER1)
            {
                printf(" 1 ");
            }
            else if (board[x][y] == PLAYER2)
            {
                printf(" 2 ");
            }
            else if (board[x][y] == PLAYER1_PROMOTED)
            { // Pièce promue du Joueur 1
                printf("[1]");
            }
            else if (board[x][y] == PLAYER2_PROMOTED)
            { // Pièce promue du Joueur 2
                printf("[2]");
            }
            printf("%s", ANSI_RESET);
        }
        printf("\n");
    }
}