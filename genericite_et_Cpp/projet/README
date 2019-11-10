# II
## 3
À ce stade, le code n'est toujours pas générique, car
seul le type des valeurs des pixels de l'image est générique, 
alors que le type de points, du domaine, et des iterateurs sont 
toujours fixés (on est notement toujours en dimension 2).
Il suffit d'ajouter en paramètre de la template la dimension de
l'image, et de rendre les autres classes et structures génériques
pour pouvoir en changer la dimension, voir même changer de type de box
ou d'image.


# Niveau 7

Pour obtenir le plus cours chemin, il suffit de calculer la carte de
distance de l'image avec un masque binaire pour contraindre au chemins
possibles, puis de partir de la destination et de remonter le gradient
jusqu'à arriver à 0. On arrive obligatoirement à la case de départ de
cette façon de par la nature de la carte de distance.
Ceci est effectué par la fonction "follow_gradient" dans tests.cc.
(on ne fait ceci que pour des images dont on a voulu calculer le
chemin, donc à priori que des images masquées)
