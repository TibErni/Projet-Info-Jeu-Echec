#include "render.h"

bool is_inside_board(int x, int y);
bool is_piece_on_path(const Board board, int x_start, int y_start, int x_end, int y_end);
bool is_valid_move(const Board board, Piece current_player, int x_start, int y_start, int x_end, int y_end);
int move_piece(Board board, Piece player, int x_start, int y_start, int x_end, int y_end);
bool has_valid_move(const Board board, Piece player);
void get_best_move_level1(const Board board, Piece player, int *x_start, int *y_start, int *x_end, int *y_end);
void ia_move(Board board, Piece player);
void get_best_move_level2(Board board, Piece player, int* x_start, int* y_start, int* x_end, int* y_end);
void get_best_move_level3(Board board, Piece player, int* x_start, int* y_start, int* x_end, int* y_end);