# I

Graphe orienté pondéré dont les noeuds sont les fragments et les poids
sont la taille du plus grand overlap entre les deux fragments. (ie le
plus grand sufixe de l'antécédent étant préfixe de l'image)


# II


# III

Soient U et V deux fragments

On cherche la plus grande frontière f de UV tq |f| <= min(|U|, |V|)


# IV


# V

Il y a au plus un chemin hamiltonien dans un graphe sans circuit, car
s'il existait deux chemins hamiltoniens différents dans un seul
graphe, cela signifierais la présence de circuits.

Trouver un chemin hamiltonien dans un graphe revient donc à chercher
le plus long chemin et à vérifier qu'il est bien de taille N.
L'absence de circuit garantie la linéarité de l'algorithme.
