# Readme du projet Colors

Les créateurs  du jeu sont Alexis Morel, Thibault Raillard et Camille Béaur. 


Ce readme va servir à présenter toutes les règles de notre jeu:

Il se joue à un ou deux joueurs, sur un plateau de huit cases sur huit. Chaque case est représentée par des couleurs différentes. Les joueurs disposent chacun de huit pions placés sur leurs premières lignes.

## Le plateau du jeu Colors :
![](https://i.imgur.com/ib1aSXy.png[/img])

## But du jeu :

Le vainqueur est le joueur qui a gagné le plus de points à la fin de toutes les manches. En cas d’égalité, une dernière manche est lancée.
La manche se termine lorsqu’un pion atteint le bout du plateau adverse ou qu’aucun déplacement de pion n’est plus possible, dans ce cas, le dernier joueur à avoir joué gagne la manche.

## Déroulement de la partie : 

**Déplacement d’un pion :** chaque pion a le droit de se déplacer en ligne droite, sur les côtés ou bien en diagonale. Le nombre de cases n’est pas limité. Le pion ne peut pas revenir en arrière et ne peut pas passer au-dessus d’une autre pièce. Enfin plusieurs pions ne peuvent pas se situer sur la même case.

![](https://i.imgur.com/5vUQ2iA.png[/img])


Lorsque le joueur 1 a fini son déplacement, c'est au tour du joueur 2 et ainsi de suite.

Pour déplacer son pion, le jeu va demander les coordonnés de la case sur laquelle le pion se situe et sur celle où il souhaite arriver (un message s'affiche si une erreur a lieu durant la saisie des valeurs). Pour bouger son pion, il va falloir écrire de la méthode suivante : ligne_départ  colonne_départ  ligne_arrivée  colonne_arrivée

![](https://i.imgur.com/Zwd89qX.png[/img])

Par exemple, pour faire avancer ce pion on devra écrire : 7 3 4 3

**Voici les coordonnés de chaque case:**

![](https://i.imgur.com/xd7oLqw.png[/img])

Au début de la partie les joueurs ont le choix de décider du nombre de manches qu’ils souhaitent faire. Dans le cas d’une partie à multi manches, si l’ un des joueurs amène un de ses pions dans le camp adverse, la manche se termine. Le vainqueur gagne 1 point et le pion qui a amené la victoire est promu. Ce nouveau pion est appelé reine et est symbolisé par :  [▲] et [▼].

**Déplacement d’une reine:** Cette pièce se déplace de la même manière que le pion mais de 5 cases maximum.

![](https://i.imgur.com/g9L1okm.png[/img])

De plus, la reine à la capacité de faire reculer un pion adverse d’une case à condition qu’il n’y ai aucun autre pion derrière celui-ci. La reine prends ainsi l’ancienne place du pion :

![](https://i.imgur.com/g4lLyhQ.png[/img])

Pour réaliser ce mouvement, le joueur 1 demande à la reine de se déplacer sur la case du pion. Cette action marche horizontalement, verticalement et en diagonal. Une reine ne peut pas faire reculer une autre reine.

Si la reine arrive à atteindre le côté adverse,  elle rapporte 2 points au joueur. Une reine ne peut pas être promue.

Si après un déplacement plus aucun mouvement n’est possible sur le terrain, alors c’est le dernier joueur à avoir déplacé son pion qui remporte la manche.

![](https://i.imgur.com/diBr4QR.png[/img])

## Jouabilité : 

Ce jeu dispose de deux modes : À deux joueurs ou bien  d’un mode “jouer contre l'ordinateur” à choisir en début de partie. 
Cet ordinateur possède trois niveaux de difficultés, allant du plus simple au plus complexe.

![](https://i.imgur.com/6tgeIpb.png[/img])

Un chronomètre est également disponible pour mesurer la durée des tours. Et à la fin de chaque manche, chaque joueur à la possibilité de voir son temps de jeu cumulé.
 
