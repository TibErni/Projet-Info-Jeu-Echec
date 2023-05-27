#include "move.h"
#include <time.h>
#include <string.h>
#include <ctype.h>

int main()
{
    srand(time(NULL));
    Board board;

    int num_rounds;
    int player1_promoted = -1;
    int player2_promoted = -1;
    int player1_score = 0;
    int player2_score = 0;

    char input[MAX_INPUT_LENGTH];
    int num_read;
    int play_with_ia; // Ajout de cette variable pour stocker le choix de l'utilisateur de jouer avec l'IA ou non.

    // Validation du nombre de manches à jouer
    char *end;
    do
    {
        printf("Entrez le nombre de manches a jouer : ");
        fgets(input, sizeof(input), stdin);
        num_rounds = strtol(input, &end, 10);
        while (isspace((unsigned char)*end))
            end++;
    } while (*end != '\0' || num_rounds <= 0);

    // Ajout du code pour demander à l'utilisateur s'il veut jouer avec l'IA ou non.
    do
    {
        printf("Voulez-vous jouer avec l'IA ? (1 pour Oui, 0 pour Non) ");
        fgets(input, sizeof(input), stdin);
        play_with_ia = strtol(input, &end, 10);
        while (isspace((unsigned char)*end))
            end++;
    } while (*end != '\0' || (play_with_ia != 0 && play_with_ia != 1));

    int ia_level; // Ajoutez cette variable en haut du main()

    // Ajoutez ce code après avoir demandé à l'utilisateur s'il veut jouer avec l'IA
    if (play_with_ia)
    {
        do
        {
            printf("Choisissez le niveau de l'IA (1 pour niveau 1, 2 pour niveau 2, 3 pour niveau 3) : ");
            fgets(input, sizeof(input), stdin);
            ia_level = strtol(input, &end, 10);
            while (isspace((unsigned char)*end))
                end++;
        } while (*end != '\0' || (ia_level != 1 && ia_level != 2 && ia_level != 3));
    }

    bool game_over = false;

    time_t start_time, end_time;
    double player1_total_time = 0, player2_total_time = 0;

    for (int i = 0; i < num_rounds && !game_over; i++)
    {
        initialize_board(board, player1_promoted, player2_promoted);
        printf("Debut de la manche %d:\n", i + 1);
        print_board(board);

        Piece current_player = PLAYER1;

        while (1)
        {
            int x_start, y_start, x_end, y_end;
            double elapsed_time;
            time_t start_time, end_time;

            if ((play_with_ia && current_player == PLAYER1) || (current_player == PLAYER2 && PLAYER2_IS_AI))
            {
                start_time = time(NULL);
                if (ia_level == 1)
                {
                    get_best_move_level1(board, current_player, &x_start, &y_start, &x_end, &y_end);
                }
                else if (ia_level == 2)
                {
                    get_best_move_level2(board, current_player, &x_start, &y_start, &x_end, &y_end);
                }
                else
                { // ia_level == 3
                    get_best_move_level3(board, current_player, &x_start, &y_start, &x_end, &y_end);
                }
                end_time = time(NULL);
                elapsed_time = difftime(end_time, start_time);
                printf("IA (joueur %d) a decide de son mouvement.\n", current_player);
            }
            else
            {
                printf("Joueur %d, entrez les coordonnees de depart et d'arrivee (x_start y_start x_end y_end) ou -1 pour quitter: ", current_player);
                start_time = time(NULL);
                if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL || strlen(input) >= MAX_INPUT_LENGTH - 1)
                {
                    printf("Erreur d'entree. Essayez encore.\n");
                    continue;
                }
                end_time = time(NULL);
                num_read = sscanf(input, "%d %d %d %d", &x_start, &y_start, &x_end, &y_end);
                if (num_read != 4)
                {
                    printf("Entree non valide. Quatre nombres entiers sont requis.\n");
                    continue;
                }
            }

            elapsed_time = difftime(end_time, start_time);
            printf("Le joueur %d a pris %.2f secondes pour effectuer ce mouvement.\n", current_player, elapsed_time);

            if (current_player == PLAYER1)
            {
                player1_total_time += elapsed_time;
            }
            else
            {
                player2_total_time += elapsed_time;
            }

            if (move_piece(board, current_player, x_start, y_start, x_end, y_end))
            {
                printf("Mouvement effectue.\n");
                print_board(board);

                if (current_player == PLAYER1 && x_end == BOARD_SIZE - 1)
                {
                    printf("Le joueur 1 a atteint le cote opposé du plateau !\n");
                    player1_promoted = y_end;
                    player1_score += (board[x_end][y_end] == PLAYER1_PROMOTED) ? 2 : 1;
                    break;
                }
                else if (current_player == PLAYER2 && x_end == 0)
                {
                    printf("Le joueur 2 a atteint le cote oppose du plateau !\n");
                    player2_promoted = y_end;
                    player2_score += (board[x_end][y_end] == PLAYER2_PROMOTED) ? 2 : 1;
                    break;
                }

                current_player = (current_player == PLAYER1) ? PLAYER2 : PLAYER1;
            }
            else
            {
                printf("Mouvement invalide. Reessayez.\n");
            }

            if (!has_valid_move(board, PLAYER1) && !has_valid_move(board, PLAYER2))
            {
                printf("Aucun mouvement possible pour les deux joueurs. Le dernier joueur ayant bouge remporte la manche !\n");
                if (current_player == PLAYER1)
                {
                    player1_score += 1;
                }
                else
                {
                    player2_score += 1;
                }
                break;
            }
        }

        printf("Le score actuel est : Joueur 1 - %d, Joueur 2 - %d\n", player1_score, player2_score);
        printf("Le temps total passe jusqu'a présent est : Joueur 1 - %.2f secondes, Joueur 2 - %.2f secondes\n", player1_total_time, player2_total_time);

        if (i == num_rounds - 1)
        { // S'il s'agit de la dernière manche
            if (player1_score > player2_score)
            {
                printf("Le joueur 1 remporte la partie !\n");
                game_over = true; // Fin du jeu
            }
            else if (player2_score > player1_score)
            {
                printf("Le joueur 2 remporte la partie !\n");
                game_over = true; // Fin du jeu
            }
            else
            { // En cas d'égalité
                printf("Il y a egalité ! Une manche supplementaire est necessaire.\n");
                num_rounds++; // Ajouter une manche supplémentaire
            }
        }
    }

    printf("Le temps total passe pour l'ensemble de la partie est : Joueur 1 - %.2f secondes, Joueur 2 - %.2f secondes\n", player1_total_time, player2_total_time);

    return 0;
}