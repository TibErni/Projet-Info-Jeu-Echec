#include "render.h"

const char *ANSI_COLORS[] = {
    "\x1b[30m",  // Noir
    "\x1b[41m",  // Fond Rouge
    "\x1b[42m",  // Fond Vert
    "\x1b[43m",  // Fond Jaune
    "\x1b[44m",  // Fond Bleu
    "\x1b[45m",  // Fond Magenta
    "\x1b[46m",  // Fond Cyan
    "\x1b[47m",  // Fond Blanc
    "\x1b[100m", // Fond Gris
    "\x1b[101m", // Fond Rouge Clair
};

// Cette constante indique le nombre total de couleurs définies dans le tableau ANSI_COLORS.
// Pour obtenir ce nombre, nous divisons la taille totale du tableau ANSI_COLORS (en octets) par la taille d'un élément unique du tableau.
const int NUM_COLORS = sizeof(ANSI_COLORS) / sizeof(ANSI_COLORS[0]);

// ANSI_RESET est une chaîne de caractères qui représente le code de contrôle ANSI pour réinitialiser toutes les propriétés de couleur et de style du texte.
// L'utilisation de cette constante permet de réinitialiser le texte à son apparence par défaut après avoir appliqué des couleurs ou des styles.
const char *ANSI_RESET = "\x1b[0m";
/**
 * La fonction initialize_board initialise l'état initial du plateau de jeu. 
 * Elle place les pièces des deux joueurs sur leurs positions de départ respectives 
 * et met le reste du plateau à vide.
 * 
 * @param board Le plateau de jeu à initialiser.
 * @param player1_promoted L'index du pion du joueur 1 qui commence comme une pièce promue.
 * @param player2_promoted L'index du pion du joueur 2 qui commence comme une pièce promue.
 */
void initialize_board(Board board, Piece player1_promoted, Piece player2_promoted) 
{
    // On parcourt chaque case du plateau
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            // Si nous sommes sur la première ligne
            if (i == 0) 
            {
                // Si le pion courant est celui qui est promu pour le joueur 1
                if (j == player1_promoted)
                {
                    // On place une pièce promue du joueur 1 sur la case
                    board[i][j] = PLAYER1_PROMOTED;
                }
                else
                {
                    // Sinon, on place une pièce normale du joueur 1
                    board[i][j] = PLAYER1;
                }
            }
            // Si nous sommes sur la dernière ligne
            else if (i == BOARD_SIZE - 1) 
            {
                // Si le pion courant est celui qui est promu pour le joueur 2
                if (j == player2_promoted) 
                {
                    // On place une pièce promue du joueur 2 sur la case
                    board[i][j] = PLAYER2_PROMOTED;
                }
                else
                {
                    // Sinon, on place une pièce normale du joueur 2
                    board[i][j] = PLAYER2;
                }
            }
            else
            {
                // Si nous ne sommes ni sur la première, ni sur la dernière ligne, 
                // la case est vide
                board[i][j] = EMPTY;
            }
        }
    }
}


/**
 * La fonction get_color_index détermine l'indice de la couleur à utiliser pour une case donnée
 * sur le plateau. Cette fonction utilise une formule simple pour obtenir un indice basé sur les 
 * coordonnées (x, y) de la case.
 * 
 * @param x La coordonnée x (horizontale) de la case sur le plateau.
 * @param y La coordonnée y (verticale) de la case sur le plateau.
 * @return L'indice de la couleur à utiliser pour la case. Cette valeur est déterminée en 
 *         ajoutant les coordonnées x et y ensemble, puis en prenant le reste de la division 
 *         par NUM_COLORS (le nombre total de couleurs disponibles).
 */
int get_color_index(int x, int y) 
{
    return (x + y) % NUM_COLORS;
}


/**
 * La fonction print_board affiche l'état actuel du plateau de jeu à l'écran. Pour chaque case du
 * plateau, elle choisit une couleur à l'aide de la fonction get_color_index et imprime soit un espace
 * vide pour une case vide, soit le symbole du joueur occupant la case. Pour les pièces promues, 
 * des crochets sont ajoutés autour du symbole du joueur.
 * 
 * @param board Le plateau de jeu à afficher. Il s'agit d'un tableau à deux dimensions de la taille 
 *        BOARD_SIZE x BOARD_SIZE, où chaque cellule contient soit EMPTY (pour une case vide), soit 
 *        PLAYER1 ou PLAYER2 (pour une case occupée par le joueur correspondant), soit 
 *        PLAYER1_PROMOTED ou PLAYER2_PROMOTED (pour une case occupée par une pièce promue du joueur 
 *        correspondant).
 */
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