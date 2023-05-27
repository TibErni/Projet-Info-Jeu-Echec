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
    int play_with_ia; // Ajout de cette variable pour stocker le choix de
                      // l'utilisateur de jouer avec l'IA ou non.

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

    // Ajout du code pour demander à l'utilisateur s'il veut jouer avec l'IA ou
    // non.
    do
    {
        printf("Voulez-vous jouer avec l'IA ? (1 pour Oui, 0 pour Non) ");
        fgets(input, sizeof(input), stdin);
        play_with_ia = strtol(input, &end, 10);
        while (isspace((unsigned char)*end))
            end++;
    } while (*end != '\0' || (play_with_ia != 0 && play_with_ia != 1));

    int ia_level; // Ajoutez cette variable en haut du main()

    // Ajoutez ce code après avoir demandé à l'utilisateur s'il veut jouer avec
    // l'IA
    if (play_with_ia)
    {
        do
        {
            printf("Choisissez le niveau de l'IA (1 pour niveau 1, 2 pour niveau 2, "
                   "3 pour niveau 3) : ");
            fgets(input, sizeof(input), stdin);
            ia_level = strtol(input, &end, 10);
            while (isspace((unsigned char)*end))
                end++;
        } while (*end != '\0' || (ia_level != 1 && ia_level != 2 && ia_level != 3));
    }

    bool game_over = false;

    time_t start_time, end_time;
    double player1_total_time = 0, player2_total_time = 0;

    // Boucle for qui effectue le nombre de manches du jeu indiqué par "num_rounds"
    // tant que la variable "game_over" est fausse.
    for (int i = 0; i < num_rounds && !game_over; i++)
    {
        // Initialisation du plateau de jeu avant chaque manche.
        initialize_board(board, player1_promoted, player2_promoted);
        // Affiche le numéro de la manche courante.
        printf("Debut de la manche %d:\n", i + 1);
        // Affiche l'état actuel du plateau de jeu.
        print_board(board);

        // Définir le joueur actuel (au début de chaque manche, le joueur 1 commence).
        Piece current_player = PLAYER1;

        // Cette boucle while se poursuit jusqu'à ce qu'une condition de rupture soit satisfaite.
        while (1)
        {
            // Déclaration de variables pour les coordonnées de départ et d'arrivée,
            // le temps écoulé, le temps de début et de fin.
            int x_start, y_start, x_end, y_end;
            double elapsed_time;
            time_t start_time, end_time;

            // Si le joueur actuel est l'IA (déterminé par les conditions dans le if),
            // alors le mouvement de l'IA est déterminé.
            if ((play_with_ia && current_player == PLAYER1) ||
                (current_player == PLAYER2 && PLAYER2_IS_AI))
            {
                // Capture le temps de début avant que l'IA ne décide du mouvement.
                start_time = time(NULL);
                // Selon le niveau de l'IA, un mouvement approprié est déterminé.
                // Le mouvement est retourné par référence via les pointeurs x_start, y_start, x_end, y_end.
                // Remarque : les fonctions get_best_move_levelX() ne sont pas définies dans ce code.
                if (ia_level == 1)
                {
                    get_best_move_level1(board, current_player, &x_start, &y_start,
                                         &x_end, &y_end);
                }
                else if (ia_level == 2)
                {
                    get_best_move_level2(board, current_player, &x_start, &y_start,
                                         &x_end, &y_end);
                }
                else
                { // ia_level == 3
                    get_best_move_level3(board, current_player, &x_start, &y_start,
                                         &x_end, &y_end);
                }
                // Capture le temps de fin après que l'IA a décidé du mouvement.
                end_time = time(NULL);
                // Calcule le temps écoulé pendant que l'IA décidait du mouvement.
                elapsed_time = difftime(end_time, start_time);
                // Annonce que l'IA a décidé de son mouvement.
                printf("IA (joueur %d) a decide de son mouvement.\n", current_player);
            }
            // Si le joueur actuel n'est pas l'IA, alors le mouvement du joueur est demandé.
            else
            {
                // Demande au joueur de saisir les coordonnées de départ et d'arrivée.
                printf("Joueur %d, entrez les coordonnees de depart et d'arrivee "
                       "(x_start y_start x_end_y_end) ou -1 pour quitter: ",
                       current_player);
                // Capture le temps de début avant que le joueur ne saisisse son mouvement.
                start_time = time(NULL);
                // Lecture de l'entrée de l'utilisateur.
                // Si l'entrée est incorrecte (par exemple, si elle est plus longue que MAX_INPUT_LENGTH),
                // un message d'erreur est affiché et la boucle recommence.
                if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL ||
                    strlen(input) >= MAX_INPUT_LENGTH - 1)
                {
                    printf("Erreur d'entree. Essayez encore.\n");
                    continue;
                }
                // Capture le temps de fin après que le joueur ait saisi son mouvement.
                end_time = time(NULL);
                // Le programme essaie de lire quatre entiers à partir de l'entrée.
                num_read = sscanf(input, "%d %d %d %d", &x_start, &y_start, &x_end, &y_end);

                // Si l'utilisateur a saisi -1, le jeu se termine.
                if (num_read >= 1 && x_start == -1)
                {
                    printf("Joueur %d a quitte le jeu.\n", current_player);
                    game_over = true; // Ce drapeau met fin au jeu
                    break;
                }

                // Si l'utilisateur n'a pas entré exactement quatre nombres,
                // un message d'erreur est affiché et la boucle recommence.
                if (num_read != 4)
                {
                    printf("Entree non valide. Quatre nombres entiers sont requis.\n");
                    continue;
                }
            }

            // Calcule le temps écoulé pendant que le joueur ou l'IA décidait du mouvement.
            elapsed_time = difftime(end_time, start_time);
            // Annonce combien de temps le joueur a mis pour effectuer son mouvement.
            printf("Le joueur %d a pris %.2f secondes pour effectuer ce mouvement.\n",
                   current_player, elapsed_time);

            // Ajoute le temps écoulé au total du joueur correspondant.
            if (current_player == PLAYER1)
            {
                player1_total_time += elapsed_time;
            }
            else
            {
                player2_total_time += elapsed_time;
            }

            // Tente de déplacer une pièce selon le mouvement spécifié.
            // Si le mouvement est valide, un message est affiché et le plateau de jeu est imprimé.
            if (move_piece(board, current_player, x_start, y_start, x_end, y_end))
            {
                printf("Mouvement effectue.\n");
                print_board(board);

                // Si le joueur actuel est le joueur 1 et qu'il a atteint le côté opposé du plateau,
                // le joueur gagne des points et la boucle while est interrompue.
                if (current_player == PLAYER1 && x_end == BOARD_SIZE - 1)
                {
                    printf("Le joueur 1 a atteint le cote oppose du plateau !\n");
                    player1_promoted = y_end;
                    player1_score += (board[x_end][y_end] == PLAYER1_PROMOTED) ? 2 : 1;
                    break;
                }
                // Si le joueur actuel est le joueur 2 et qu'il a atteint le côté opposé du plateau,
                // le joueur gagne des points et la boucle while est interrompue.
                else if (current_player == PLAYER2 && x_end == 0)
                {
                    printf("Le joueur 2 a atteint le cote oppose du plateau !\n");
                    player2_promoted = y_end;
                    player2_score += (board[x_end][y_end] == PLAYER2_PROMOTED) ? 2 : 1;
                    break;
                }

                // Si le mouvement est valide, c'est au tour de l'autre joueur.
                current_player = (current_player == PLAYER1) ? PLAYER2 : PLAYER1;
            }
            // Si le mouvement n'est pas valide, un message est affiché et la boucle continue,
            // permettant au même joueur de saisir un nouveau mouvement.
            else
            {
                printf("Mouvement invalide. Reessayez.\n");
            }

            // Si aucun joueur n'a de mouvement valide, la manche se termine.
            if (!has_valid_move(board, PLAYER1) && !has_valid_move(board, PLAYER2))
            {
                printf("Aucun mouvement possible pour les deux joueurs. Le dernier "
                       "joueur ayant bouge remporte la manche !\n");
                // Le joueur qui a bougé en dernier obtient un point.
                if (current_player == PLAYER2)
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

        // Après chaque manche, le score et le temps total sont affichés.
        printf("Le score actuel est : Joueur 1 - %d, Joueur 2 - %d\n",
               player1_score, player2_score);
        printf("Le temps total passe jusqu'a present est : Joueur 1 - %.2f "
               "secondes, Joueur 2 - %.2f secondes\n",
               player1_total_time, player2_total_time);

        // Si c'était la dernière manche...
        if (i == num_rounds - 1)
        {
            // ...et que le joueur 1 a plus de points, le joueur 1 est déclaré gagnant.
            if (player1_score > player2_score)
            {
                printf("Le joueur 1 remporte la partie !\n");
                game_over = true; // Le jeu se termine
            }
            // ...ou que le joueur 2 a plus de points, le joueur 2 est déclaré gagnant.
            else if (player2_score > player1_score)
            {
                printf("Le joueur 2 remporte la partie !\n");
                game_over = true; // Le jeu se termine
            }
            // ...ou que les deux joueurs ont le même nombre de points, une manche supplémentaire est ajoutée.
            else
            {
                printf("Il y a egalité ! Une manche supplémentaire est necessaire.\n");
                num_rounds++; // Une manche supplémentaire est ajoutée
            }
        }
    }

    printf("Le temps total passe pour l'ensemble de la partie est : Joueur 1 - "
           "%.2f secondes, Joueur 2 - %.2f secondes\n",
           player1_total_time, player2_total_time);

    return 0;
}