#include "move.h"

bool is_inside_board(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

bool is_piece_on_path(const Board board, int x_start, int y_start, int x_end, int y_end) {
    int dx = x_end - x_start;
    int dy = y_end - y_start;
    int x_step = (dx != 0) ? (dx > 0 ? 1 : -1) : 0;
    int y_step = (dy != 0) ? (dy > 0 ? 1 : -1) : 0;
    int x, y;

    for (x = x_start + x_step, y = y_start + y_step; x != x_end || y != y_end; x += x_step, y += y_step) {
        if (board[x][y] != EMPTY) {
            return true;
        }
    }

    return false;
}

bool is_valid_move(const Board board, Piece current_player, int x_start, int y_start, int x_end, int y_end) {
    int dx = x_end - x_start;
    int dy = y_end - y_start;
    Piece start_piece = board[x_start][y_start];

    if (!is_inside_board(x_end, y_end)) { //  faux si coup en dehors du terrain de jeu
        return false;
    }

    if (start_piece != current_player && start_piece != current_player + 2 || board[x_end][y_end] != EMPTY) { // faux si la case est déjà occupé ou non vide
        return false;
    }

    if (start_piece == current_player) {
        if (current_player == PLAYER1) { // vérifie que le joueur 1 fais un coup en diagonal correct, ou un coup sur la largeur ou sur la longeur
            if (!((dx == 1 && abs(dy) == dx) || (dx == 1 && dy == 0) || (dx == 0 && abs(dy) == 1))) {
                return false;
            }
        } else if (current_player == PLAYER2) { // vérifie que le joueur 2 fais un coup en diagonal correct, ou un coup sur la largeur ou sur la longeur
            if (!((dx == -1 && abs(dy) == dx) || (dx == -1 && dy == 0) || (dx == 0 && abs(dy) == 1))) {
                return false;
            }
        }
    } else if (start_piece == current_player + 2) {
        if (!(abs(dx) <= 1 && abs(dy) <= 1)) {
            return false;
        }
    }

    if (is_piece_on_path(board, x_start, y_start, x_end, y_end)) {
        return false;
    }

    return true;
}

int move_piece(Board board, Piece player, int x_start, int y_start, int x_end, int y_end) {
    Piece start_piece = board[x_start][y_start];
    Piece end_piece = board[x_end][y_end];

    if (start_piece != player && start_piece != player + 2) {
        return 0;  // La pièce de départ n'appartient pas au joueur actuel
    }

    if (end_piece == player || end_piece == player + 2) {
        return 0;  // La case d'arrivée est occupée par une pièce alliée
    }

    int dx = x_end - x_start;
    int dy = y_end - y_start;

    if (is_piece_on_path(board, x_start, y_start, x_end, y_end)) {
        return 0;  // Il y a une pièce sur le chemin
    }

    // Vérifiez si la pièce est promue et pousse une pièce adverse qui n'est pas promue
    if (start_piece == player + 2 && end_piece == 3 - player && end_piece != player + 4 && end_piece != 3 - player + 2) {
        // Calculer la position à laquelle la pièce repoussée doit se déplacer
        int x_push = x_end + (dx == 0 ? 0 : (dx > 0 ? 1 : -1));
        int y_push = y_end + (dy == 0 ? 0 : (dy > 0 ? 1 : -1));
        
        // Vérifiez si la pièce peut être poussée
        if (is_inside_board(x_push, y_push) && board[x_push][y_push] == EMPTY) {
            board[x_push][y_push] = end_piece;
            board[x_end][y_end] = start_piece;
            board[x_start][y_start] = EMPTY;
            return 1;
        } else {
            return 0; // Mouvement invalide si la pièce ne peut pas être poussée
        }
    }

    if (start_piece == player) {
        // Mouvement d'une pièce normale
        if ((player == PLAYER1 && dx >= 0) || (player == PLAYER2 && dx <= 0)) {
            if (dx == 0 || dy == 0 || abs(dx) == abs(dy)) {
                board[x_end][y_end] = player;
                board[x_start][y_start] = EMPTY;
                return 1;
            }
        }
    } else if (start_piece == player + 2) {
    // La pièce est promue
    if ((player == PLAYER1 && dx >= 0) || (player == PLAYER2 && dx <= 0)) {
        if ((dx == 0 || dy == 0 || abs(dx) == abs(dy)) && abs(dx) <= 5 && abs(dy) <= 5) {
            // Si la pièce de fin est une pièce ennemie promue, la pièce promue ne peut pas la pousser
            if (end_piece == 3 - player + 2) {
                return 0;
            }
            // Déplace la pièce promue normalement
            board[x_end][y_end] = player + 2;
            board[x_start][y_start] = EMPTY;
            return 1;
        }
    }
}


    return 0;  // Le mouvement est invalide
}

bool has_valid_move(const Board board, Piece player) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            // Si la pièce appartient au joueur actuel
            if (board[x][y] == player || board[x][y] == player + 2) {
                // Essayez tous les mouvements possibles pour cette pièce
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        int x_end = x + dx;
                        int y_end = y + dy;
                        // Si le mouvement est valide, le joueur peut bouger
                        if (is_valid_move(board, player, x, y, x_end, y_end)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    // Si aucun mouvement valide n'est trouvé, le joueur ne peut pas bouger
    return false;
}

void get_best_move_level1(const Board board, Piece player, int *x_start, int *y_start, int *x_end, int *y_end) {
    int winning_x_start = -1;
    int winning_y_start = -1;
    int winning_x_end = -1;
    int winning_y_end = -1;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != player) continue;

            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int new_i = i;
                    int new_j = j;

                    // Determine how far we can move in this direction
                    while (new_i + di >= 0 && new_i + di < BOARD_SIZE && new_j + dj >= 0 && new_j + dj < BOARD_SIZE && board[new_i + di][new_j + dj] == EMPTY) {
                        new_i += di;
                        new_j += dj;
                    }

                    // If the move results in winning the game, record it
                    if (new_i == BOARD_SIZE - 1 && new_i != i) {
                        winning_x_start = i;
                        winning_y_start = j;
                        winning_x_end = new_i;
                        winning_y_end = new_j;
                    }
                }
            }
        }
    }

    // If a winning move was found, perform it
    if (winning_x_start != -1) {
        *x_start = winning_x_start;
        *y_start = winning_y_start;
        *x_end = winning_x_end;
        *y_end = winning_y_end;
    }
    // Otherwise, select a random valid move
    else {
        while (1) {
            *x_start = rand() % BOARD_SIZE;
            *y_start = rand() % BOARD_SIZE;
            *x_end = *x_start + (rand() % 3 - 1);
            *y_end = *y_start + (rand() % 3 - 1);

            if (*x_end >= 0 && *x_end < BOARD_SIZE && *y_end >= 0 && *y_end < BOARD_SIZE && board[*x_end][*y_end] == EMPTY && is_valid_move(board, player, *x_start, *y_start, *x_end, *y_end)) {
                break;
            }
        }
    }
}

void ia_move(Board board, Piece player) {
    while (1) {
        int x_start = rand() % BOARD_SIZE;
        int y_start = rand() % BOARD_SIZE;
        int x_end = rand() % BOARD_SIZE;
        int y_end = rand() % BOARD_SIZE;

        if (move_piece(board, player, x_start, y_start, x_end, y_end)) {
            printf("IA a déplacé une pièce de (%d, %d) à (%d, %d).\n", x_start, y_start, x_end, y_end);
            break;
        }
    }
}

void get_best_move_level2(Board board, Piece player, int* x_start, int* y_start, int* x_end, int* y_end) {
    int best_score = -1;
    int winning_x_start = -1;
    int winning_y_start = -1;
    int winning_x_end = -1;
    int winning_y_end = -1;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != player) continue;

            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int new_i = i;
                    int new_j = j;
                    int steps = 0;

                    // Determine how far we can move in this direction
                    while (new_i + di >= 0 && new_i + di < BOARD_SIZE && new_j + dj >= 0 && new_j + dj < BOARD_SIZE && board[new_i + di][new_j + dj] == EMPTY) {
                        new_i += di;
                        new_j += dj;
                        steps++;

                        // If the move results in winning the game, record it
                        if (new_i == BOARD_SIZE - 1) {
                            winning_x_start = i;
                            winning_y_start = j;
                            winning_x_end = new_i;
                            winning_y_end = new_j;
                            break;
                        }

                        // If we've moved 4 steps and this is not a winning move, break
                        if (steps == 4) {
                            break;
                        }
                    }

                    int score = new_i;  // Higher score for moving towards the end of the board
                    if (new_j > 0 && new_j < BOARD_SIZE - 1) score++;  // Higher score for staying in the middle of the board

                    if (score > best_score) {
                        best_score = score;
                        *x_start = i;
                        *y_start = j;
                        *x_end = new_i;
                        *y_end = new_j;
                    }
                }
            }
        }
    }

    // If a winning move was found, perform it
    if (winning_x_start != -1) {
        *x_start = winning_x_start;
        *y_start = winning_y_start;
        *x_end = winning_x_end;
        *y_end = winning_y_end;
    }
}

void get_best_move_level3(Board board, Piece player, int* x_start, int* y_start, int* x_end, int* y_end) {
    int best_distance = -1;
    int distance;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != player) continue;

            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int new_i = i;
                    int new_j = j;

                    // Continue moving in this direction until we hit a non-empty square or the edge of the board
                    while (1) {
                        new_i += di;
                        new_j += dj;
                        if (new_i < 0 || new_i >= BOARD_SIZE || new_j < 0 || new_j >= BOARD_SIZE || board[new_i][new_j] != EMPTY) {
                            new_i -= di;  // Step back to the last valid position
                            new_j -= dj;
                            break;
                        }
                    }

                    distance = abs(new_i - i);  // How far did we move in the x-direction? (Assuming the board is square)
                    if (distance > best_distance || new_i == BOARD_SIZE - 1) {  // Check if the move allows us to win the game
                        best_distance = distance;
                        *x_start = i;
                        *y_start = j;
                        *x_end = new_i;
                        *y_end = new_j;
                    }
                }
            }
        }
    }
}