#include "render.h"


/**
 * Cette fonction vérifie si une position donnée (x, y) est bien à l'intérieur des limites du plateau de jeu.
 * Elle renvoie true si la position est à l'intérieur des limites et false sinon.
 *
 * @param x La coordonnée x (ligne) de la position à vérifier.
 * @param y La coordonnée y (colonne) de la position à vérifier.
 * @return  true si la position est dans les limites du plateau, false sinon.
 */
bool is_inside_board(int x, int y)
{
    // Vérifie que x et y sont bien dans les limites du plateau [0, BOARD_SIZE-1]
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

/**
 * Cette fonction vérifie si une pièce se trouve sur le chemin entre deux positions données sur le plateau.
 * Elle renvoie true si une pièce est trouvée sur le chemin, et false sinon.
 *
 * @param board Le plateau de jeu.
 * @param x_start, y_start Les coordonnées de la position de départ.
 * @param x_end, y_end Les coordonnées de la position de fin.
 * @return  true si une pièce est trouvée sur le chemin, false sinon.
 */
bool is_piece_on_path(const Board board, int x_start, int y_start, int x_end, int y_end)
{
    // Calculer la différence entre les coordonnées de départ et de fin
    int dx = x_end - x_start;
    int dy = y_end - y_start;

    // Déterminer les étapes à faire pour se déplacer le long de l'axe x et y
    int x_step = (dx != 0) ? (dx > 0 ? 1 : -1) : 0;
    int y_step = (dy != 0) ? (dy > 0 ? 1 : -1) : 0;

    int x, y;

    // Parcourir le chemin entre la position de départ et la position de fin
    for (x = x_start + x_step, y = y_start + y_step; x != x_end || y != y_end; x += x_step, y += y_step)
    {
        // Si une pièce est trouvée sur le chemin, retourner true
        if (board[x][y] != EMPTY)
        {
            return true;
        }
    }

    // Si aucune pièce n'est trouvée sur le chemin, retourner false
    return false;
}

/**
 * Vérifie si un mouvement est valide dans le jeu.
 * Pour qu'un mouvement soit valide, il doit respecter plusieurs conditions :
 * - Le mouvement doit rester à l'intérieur du plateau de jeu.
 * - Le mouvement doit être fait par le joueur courant.
 * - Le mouvement doit respecter les règles de déplacement des pièces.
 * - Il ne doit pas y avoir de pièce sur le chemin.
 *
 * @param board Le plateau de jeu.
 * @param current_player Le joueur actuel.
 * @param x_start, y_start Les coordonnées de la position de départ.
 * @param x_end, y_end Les coordonnées de la position de fin.
 * @return  true si le mouvement est valide, false sinon.
 */
bool is_valid_move(const Board board, Piece current_player, int x_start, int y_start, int x_end, int y_end)
{
    // Calcule la différence entre les positions de départ et d'arrivée
    int dx = x_end - x_start;
    int dy = y_end - y_start;

    // Récupère la pièce à la position de départ
    Piece start_piece = board[x_start][y_start];

    // Vérifie si la position de fin est à l'intérieur du plateau de jeu
    if (!is_inside_board(x_end, y_end))
    { // Renvoie false si le mouvement sort du plateau de jeu
        return false;
    }

    // Vérifie si la pièce à la position de départ appartient au joueur courant et si la case d'arrivée est vide
    if (start_piece != current_player && start_piece != current_player + 2 || board[x_end][y_end] != EMPTY)
    { // Renvoie false si la case d'arrivée est déjà occupée ou si la pièce à la position de départ n'appartient pas au joueur courant
        return false;
    }

    // Vérifie si les mouvements sont conformes aux règles de déplacement des pièces pour chaque type de pièce et chaque joueur
    if (start_piece == current_player)
    {
        if (current_player == PLAYER1)
        { // Vérifie que le joueur 1 fait un mouvement valide (en diagonale, horizontalement ou verticalement)
            if (!((dx == 1 && abs(dy) == dx) || (dx == 1 && dy == 0) || (dx == 0 && abs(dy) == 1)))
            {
                return false;
            }
        }
        else if (current_player == PLAYER2)
        { // Vérifie que le joueur 2 fait un mouvement valide (en diagonale, horizontalement ou verticalement)
            if (!((dx == -1 && abs(dy) == dx) || (dx == -1 && dy == 0) || (dx == 0 && abs(dy) == 1)))
            {
                return false;
            }
        }
    }
    else if (start_piece == current_player + 2)
    { // Vérifie que la pièce promue fait un mouvement valide (ne dépasse pas un mouvement d'une case en n'importe quelle direction)
        if (!(abs(dx) <= 1 && abs(dy) <= 1))
        {
            return false;
        }
    }

    // Vérifie si une autre pièce est sur le chemin du mouvement
    if (is_piece_on_path(board, x_start, y_start, x_end, y_end))
    { // Renvoie false si une autre pièce est sur le chemin du mouvement
        return false;
    }

    // Si toutes les conditions précédentes sont respectées, le mouvement est considéré comme valide
    return true;
}

/**
 * Déplace une pièce sur le plateau.
 * Cette fonction met à jour le plateau de jeu en fonction des mouvements de la pièce.
 * Elle vérifie également si le mouvement est valide et renvoie un code d'erreur si ce n'est pas le cas.
 *
 * @param board Le plateau de jeu.
 * @param player Le joueur qui fait le mouvement.
 * @param x_start, y_start Les coordonnées de la position de départ.
 * @param x_end, y_end Les coordonnées de la position de fin.
 * @return  1 si le mouvement est réussi, 0 sinon.
 */
int move_piece(Board board, Piece player, int x_start, int y_start, int x_end, int y_end)
{
    Piece start_piece = board[x_start][y_start];
    Piece end_piece = board[x_end][y_end];

    if (start_piece != player && start_piece != player + 2)
    {
        return 0; // Renvoie 0 si la pièce de départ n'appartient pas au joueur actuel
    }

    if (!(board[x_end][y_end] == EMPTY || (start_piece == player + 2 && end_piece == 3 - player && end_piece != player + 4 && end_piece != 3 - player + 2)))
    {
        return 0; // Renvoie 0 si la case de destination n'est pas vide ou n'est pas occupée par une pièce ennemie non promue
    }

    int dx = x_end - x_start;
    int dy = y_end - y_start;

    if (start_piece == player && is_piece_on_path(board, x_start, y_start, x_end, y_end))
    {
        return 0; // Renvoie 0 si une pièce non promue essaie de se déplacer et qu'il y a une pièce sur le chemin
    }

    // Vérifie si la pièce est promue et essaie de pousser une pièce ennemie non promue
    if (start_piece == player + 2 && end_piece == 3 - player && end_piece != player + 4 && end_piece != 3 - player + 2)
    {
        // Calculer la position à laquelle la pièce poussée doit se déplacer
        int x_push = x_end + (dx == 0 ? 0 : (dx > 0 ? 1 : -1));
        int y_push = y_end + (dy == 0 ? 0 : (dy > 0 ? 1 : -1));

        // Vérifie si la pièce poussée peut être déplacée à la position calculée
        if (is_inside_board(x_push, y_push) && board[x_push][y_push] == EMPTY)
        {
            board[x_push][y_push] = end_piece; // Déplace la pièce poussée
            board[x_end][y_end] = start_piece; // Déplace la pièce qui pousse
            board[x_start][y_start] = EMPTY;   // Libère la case de départ
            return 1;                          // Renvoie 1 pour signaler un mouvement valide
        }
        else
        {
            return 0; // Renvoie 0 si le mouvement n'est pas valide (la pièce poussée ne peut pas être déplacée)
        }
    }

    if (start_piece == player)
    {
        // Mouvement d'une pièce non promue
        if ((player == PLAYER1 && dx >= 0) || (player == PLAYER2 && dx <= 0))
        {
            if (dx == 0 || dy == 0 || abs(dx) == abs(dy))
            {
                board[x_end][y_end] = player;    // Déplace la pièce
                board[x_start][y_start] = EMPTY; // Libère la case de départ
                return 1;                        // Renvoie 1 pour signaler un mouvement valide
            }
        }
    }
    // Mouvement d'une pièce promue
    else if (start_piece == player + 2)
    {
        if ((player == PLAYER1 && dx >= 0) || (player == PLAYER2 && dx <= 0))
        {
            if ((dx == 0 || dy == 0 || abs(dx) == abs(dy)) && abs(dx) <= 5 &&
                abs(dy) <= 5)
            {
                // Si la pièce de fin est une pièce ennemie promue, la pièce promue ne peut pas la pousser
                if (end_piece == 3 - player + 2)
                {
                    return 0; // Renvoie 0 si le mouvement est invalide (tentative de pousser une pièce ennemie promue)
                }
                // Vérifier si une pièce est sur le chemin de la pièce promue
                if (is_piece_on_path(board, x_start, y_start, x_end, y_end))
                {
                    return 0; // Renvoie 0 si une pièce est sur le chemin de la pièce promue
                }
                // Déplace la pièce promue normalement
                board[x_end][y_end] = player + 2; // Déplace la pièce promue
                board[x_start][y_start] = EMPTY;  // Libère la case de départ
                return 1;                         // Renvoie 1 pour signaler un mouvement valide
            }
        }
    }

    return 0; // Le mouvement est invalide si aucun des cas ci-dessus ne s'est vérifié
}

/**
 * Vérifie si le joueur a au moins un mouvement valide sur le plateau.
 * Cette fonction parcourt l'ensemble du plateau de jeu pour trouver une pièce appartenant au joueur.
 * Pour chaque pièce trouvée, elle vérifie tous les mouvements possibles.
 * Un mouvement valide est déterminé par la fonction is_valid_move().
 *
 * @param board Le plateau de jeu.
 * @param player Le joueur à vérifier.
 * @return true si le joueur a au moins un mouvement valide, false sinon.
 */
bool has_valid_move(const Board board, Piece player)
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            // Si la pièce appartient au joueur actuel
            if (board[x][y] == player || board[x][y] == player + 2)
            {
                // Essayez tous les mouvements possibles pour cette pièce
                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        if (dx == 0 && dy == 0)
                            continue;
                        int x_end = x + dx;
                        int y_end = y + dy;
                        // Si le mouvement est valide, le joueur peut bouger
                        if (is_valid_move(board, player, x, y, x_end, y_end))
                        {
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

/**
 * Effectue un mouvement aléatoire pour l'IA dans le jeu.
 * Cette fonction génère des positions aléatoires pour la pièce à bouger et la destination du mouvement.
 * Elle continue à générer des mouvements aléatoires jusqu'à ce qu'un mouvement valide soit trouvé.
 * Une fois un mouvement valide trouvé, elle effectue ce mouvement et affiche les coordonnées de ce mouvement.
 *
 * @param board Le plateau de jeu.
 * @param player Le joueur (dans ce cas, l'IA).
 */
void ia_move(Board board, Piece player)
{
    // Cette boucle continue jusqu'à ce qu'un mouvement valide soit effectué
    while (1)
    {
        // Générer des coordonnées aléatoires pour la pièce à bouger (x_start, y_start)
        int x_start = rand() % BOARD_SIZE;
        int y_start = rand() % BOARD_SIZE;

        // Générer des coordonnées aléatoires pour la destination du mouvement (x_end, y_end)
        int x_end = rand() % BOARD_SIZE;
        int y_end = rand() % BOARD_SIZE;

        // Si le mouvement est valide, effectuer le mouvement
        if (move_piece(board, player, x_start, y_start, x_end, y_end))
        {
            // Afficher les coordonnées du mouvement
            printf("IA a déplacé une pièce de (%d, %d) à (%d, %d).\n", x_start, y_start, x_end, y_end);

            // Quitter la boucle une fois le mouvement effectué
            break;
        }
    }
}

/**
 * Pour une IA de niveau 1, détermine le meilleur mouvement à effectuer.
 * Cette fonction cherche d'abord un mouvement gagnant, si un tel mouvement existe.
 * Si un mouvement gagnant est trouvé, il est enregistré.
 * Si aucun mouvement gagnant n'est trouvé, un mouvement valide aléatoire est choisi.
 *
 * @param board Le plateau de jeu.
 * @param player Le joueur (dans ce cas, l'IA).
 * @param x_start, y_start Pointeurs vers les variables où les coordonnées du mouvement de départ seront stockées.
 * @param x_end, y_end Pointeurs vers les variables où les coordonnées du mouvement de fin seront stockées.
 */
void get_best_move_level1(const Board board, Piece player, int *x_start, int *y_start, int *x_end, int *y_end)
{
    // Variables pour stocker le mouvement gagnant, s'il existe
    int winning_x_start = -1;
    int winning_y_start = -1;
    int winning_x_end = -1;
    int winning_y_end = -1;

    // Parcourir l'ensemble du plateau
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            // Si la pièce à la position (i, j) n'appartient pas au joueur, passer à l'itération suivante
            if (board[i][j] != player)
                continue;

            // Essayer tous les mouvements possibles à partir de cette position
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    // Nouvelles coordonnées après le mouvement
                    int new_i = i;
                    int new_j = j;

                    // Déterminer jusqu'où nous pouvons nous déplacer dans cette direction
                    while (new_i + di >= 0 && new_i + di < BOARD_SIZE && new_j + dj >= 0 && new_j + dj < BOARD_SIZE && board[new_i + di][new_j + dj] == EMPTY)
                    {
                        new_i += di;
                        new_j += dj;
                    }

                    // Si le mouvement aboutit à la victoire dans le jeu, l'enregistrer
                    if (new_i == BOARD_SIZE - 1 && new_i != i)
                    {
                        winning_x_start = i;
                        winning_y_start = j;
                        winning_x_end = new_i;
                        winning_y_end = new_j;
                    }
                }
            }
        }
    }

    // Si un mouvement gagnant a été trouvé, effectuez-le
    if (winning_x_start != -1)
    {
        *x_start = winning_x_start;
        *y_start = winning_y_start;
        *x_end = winning_x_end;
        *y_end = winning_y_end;
    }
    // Sinon, choisissez un mouvement valide aléatoire
    else
    {
        while (1)
        {
            *x_start = rand() % BOARD_SIZE;
            *y_start = rand() % BOARD_SIZE;
            *x_end = *x_start + (rand() % 3 - 1);
            *y_end = *y_start + (rand() % 3 - 1);

            // Si le coup est dans le tableau et est valide
            if (*x_end >= 0 && *x_end < BOARD_SIZE && *y_end >= 0 && *y_end < BOARD_SIZE && board[*x_end][*y_end] == EMPTY && is_valid_move(board, player, *x_start, *y_start, *x_end, *y_end))
            {
                // Quitte la boucle et utilise ces coordonnées de déplacement
                break;
            }
        }
    }
}

/**
 * Fonction pour obtenir le meilleur coup pour le joueur IA au niveau 2.
 * À ce niveau, l'IA calcule le score pour chaque coup possible et effectue le coup avec le score le plus élevé.
 * Le score est basé sur la position du coup sur le plateau.
 * Un score plus élevé est attribué pour se déplacer vers la fin du plateau et pour rester au milieu du plateau.
 *
 * @param board Le plateau de jeu.
 * @param player Le joueur actuel (dans ce cas, l'IA).
 * @param x_start, y_start Pointeurs vers les coordonnées de départ du coup choisi.
 * @param x_end, y_end Pointeurs vers les coordonnées de fin du coup choisi.
 */
void get_best_move_level2(Board board, Piece player, int *x_start, int *y_start, int *x_end, int *y_end)
{
    // Initialiser le score le plus élevé à -1 et les coordonnées du coup gagnant à -1
    int best_score = -1;
    int winning_x_start = -1;
    int winning_y_start = -1;
    int winning_x_end = -1;
    int winning_y_end = -1;

    // Parcourir l'ensemble du plateau
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            // Si la pièce à la position (i, j) n'appartient pas au joueur, passer à la suivante
            if (board[i][j] != player)
                continue;

            // Essayer tous les mouvements possibles pour cette pièce
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int new_i = i;
                    int new_j = j;
                    int steps = 0;

                    // Déterminer jusqu'où nous pouvons nous déplacer dans cette direction
                    while (new_i + di >= 0 && new_i + di < BOARD_SIZE && new_j + dj >= 0 && new_j + dj < BOARD_SIZE && board[new_i + di][new_j + dj] == EMPTY)
                    {
                        new_i += di;
                        new_j += dj;
                        steps++;

                        // Si le mouvement aboutit à gagner la partie, l'enregistrer
                        if (new_i == BOARD_SIZE - 1)
                        {
                            winning_x_start = i;
                            winning_y_start = j;
                            winning_x_end = new_i;
                            winning_y_end = new_j;
                            break;
                        }

                        // Si nous avons fait 4 pas et que ce n'est pas un mouvement gagnant, interrompre la boucle
                        if (steps == 4)
                        {
                            break;
                        }
                    }

                    // Plus le score est élevé, plus on se rapproche de la fin du plateau
                    int score = new_i;
                    // Un score plus élevé pour rester au milieu du plateau
                    if (new_j > 0 && new_j < BOARD_SIZE - 1)
                        score++;

                    // Si le score est meilleur que le score actuel, mettre à jour le coup le plus prometteur
                    if (score > best_score)
                    {
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

    // Si un mouvement gagnant a été trouvé, l'exécuter
    if (winning_x_start != -1)
    {
        *x_start = winning_x_start;
        *y_start = winning_y_start;
        *x_end = winning_x_end;
        *y_end = winning_y_end;
    }
}

/**
 * Fonction pour déterminer le meilleur mouvement pour l'IA niveau 3.
 * Cette IA tente de maximiser la distance parcourue dans chaque déplacement.
 * Si plusieurs mouvements ont la même distance maximale, l'IA sélectionne le dernier trouvé.
 * Si un mouvement permet à l'IA de gagner immédiatement le jeu, ce mouvement est sélectionné.
 *
 * @param board Le plateau de jeu.
 * @param player Le joueur qui est l'IA.
 * @param x_start, y_start Pointeurs vers des entiers où les coordonnées de départ du meilleur mouvement seront stockées.
 * @param x_end, y_end Pointeurs vers des entiers où les coordonnées de fin du meilleur mouvement seront stockées.
 */
void get_best_move_level3(Board board, Piece player, int *x_start, int *y_start, int *x_end, int *y_end)
{
    int best_distance = -1; // Meilleure distance trouvée jusqu'à présent
    int distance;           // Distance pour le mouvement actuel

    // Parcourir toutes les cases du plateau
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            // Si la pièce n'appartient pas au joueur, passer à la prochaine
            if (board[i][j] != player)
                continue;

            // Parcourir toutes les directions possibles
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int new_i = i;
                    int new_j = j;

                    // Continuez à avancer dans cette direction jusqu'à ce que nous atteignions une case non vide ou le bord du plateau
                    while (1)
                    {
                        new_i += di;
                        new_j += dj;
                        if (new_i < 0 || new_i >= BOARD_SIZE || new_j < 0 || new_j >= BOARD_SIZE || board[new_i][new_j] != EMPTY)
                        {
                            new_i -= di; // Revenir à la dernière position valide
                            new_j -= dj;
                            break;
                        }
                    }

                    // Calculer combien nous nous sommes déplacés dans la direction x ? (En supposant que le plateau est carré)
                    distance = abs(new_i - i);
                    if (distance > best_distance || new_i == BOARD_SIZE - 1) // Vérifier si le mouvement nous permet de gagner le jeu
                    {
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