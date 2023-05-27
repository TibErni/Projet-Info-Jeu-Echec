Readme du projet colors.



Ce jeu colors a été créé par Alexis Morel, Thibault Raillard et Camille Béaur. 



Ce readme va servir à présenter toutes les règles de notre jeu:

Le jeu se joue à deux joueurs, sur un plateau de huit cases sur huit. Chaque case est coloré par huit couleurs différentes. Chaque joueur à en sa possession 8 pions placés sur leurs premières lignes.




Exemple de plateau de jeu :







But du jeu :

Le vainqueur est le joueur qui a le plus de points à la fin de toutes les manches, en cas d’égalité, une dernière manche est lancée.
La manche se termine lorsqu’un pion atteint le bout du plateau adverse ou que plus aucun pion ne peut se déplacer, dans ce cas, le dernier joueur à avoir joué gagne. 




Déroulement de la partie : 

Au début de chaque manche, tout le plateau de jeu est créé de manière aléatoire sauf la première et dernière ligne qui sont fixes.

Le déplacement d’un pion : chaque pion a le droit de se déplacer en ligne droite ou sur les côtés ou en diagonales du nombre de case qu’il veut. Le pion ne peut pas retourner en arrière et ne peut pas passer au dessus d’une autre pièce, de plus plusieurs pion ne peuvent pas se situer sur la même case: 



Lorsque le joueur 1 a fini son déplacement, il déplace son pion sur une case d’une certaine couleur (par exemple rouge), le joueur 2 serra alors contraint de jouer le pion de cette même couleur là (ici rouge). Si il ne peut déplacer ce pion (pion encerclé par exemple) alors le tour du joueur 2 est sauté et c’est de nouveau au joueur 1 de jouer également cette même couleur (rouge). Si le joueur 1 ne peut également pas jouer alors, le vainqueur est le dernier joueur à avoir déplacer un pion donc dans ce cas le joueur 1.
Afin de déplacer son pion, le jeu va demander des coordonnés de la case sur laquelle le pion se situe et sur celle ou il va arriver (un message d’erreur s'affiche si une erreur a lieu durant la saisie des valeurs). Pour déplacer son pion, il va falloir écrire de cette manière : 
ligne_départ  colonne_départ  ligne_arrivé  colone_arrivé.


Ici pour faire avancer ce pion on devra écrire : 7 3 4 3

Voici les coordonnés de chaque case:

0 0
0 1
0 2
0 3
0 4
0 5
0 6
0 7
1 0
1 1
1 2
1 3
1 4
1 5
1 6
1 7
2 0
2 1
2 2
2 3
2 4
2 5
2 6
2 7
3 0
3 1
3 2
3 3
3 4
3 5
3 6
3 7
4 0
4 1
4 2
4 3
4 4
4 5
4 6
4 7
5 0
5 1
5 2
5 3
5 4
5 5
5 6
5 7
6 0
6 1
6 2
6 3
6 4
6 5
6 6
6 7
7 0
7 1
7 2
7 3
7 4
7 5
7 6
7 7



Au début de la partie on a le choix de décider du nombre de manches que l’on souhaite faire. Dans ce cas, si un des joueurs amène un de ses pions dans le camp adverse, la manche se termine, le vainqueur gagne 1 point et le pion qui a amené la victoire est promu. Ce nouveau pion est appelé reine et ressemble à ça :  [▲] et [▼]. 

Déplacement d’une reine: La reine se déplace de la même manière que le pion mais de seulement 5 cases maximum:

De plus la reine à la possibilité de faire reculer un pion adverse d’une case à condition qu’il n’y ai aucun pion derrière celui-ci, la reine prends ainsi l’ancienne place du pion : 

Pour cela le joueur 1 demande à la reine de se déplacer sur la case du pion jaune. A la fin de ce déplacement, la case sur laquelle le pion du joueur 2 recule indique la couleur qui doit être jouée au tour suivant (ici vert). Une reine ne peut pas faire reculer une autre reine.

Si la reine arrive à atteindre le côté adversaire, elle rapporte 2 points au joueur. Une reine ne peut pas être promue.
