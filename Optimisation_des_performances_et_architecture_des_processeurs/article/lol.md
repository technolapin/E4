# Algo naïf

* expliquer le principe

# Algo O(n) et algos dérivés

* expliquer le principe
* expliquer que celui en O(log(n)) est certe rapide, mais est très complexe.
* mentionner la borne inférieure de Gil-Werman

# Algo en O(1)

* Expliquer le principe
* Expliquer pourquoi la borne de Gil-Werman ne s'applique pas à cet algo
* problème de la taille limité des caches processeurs ( on divise alors l'image en bandes verticales à traîter séparément)
* multilevel histograms (garder un histogramme ne gardant que les bit de poid fort pour aller plus vite)
* Mise à jour conditionnelle du kernel (faire tout l'algo avec les histogrammes aproximatifs et n'accéder aux vrais valeurs que si nécessaire)
* marche pour les images en couleurs tout aussi bien, (mais on traîte alors des bandes d'images plus fines)
* en N-dimensions, marche en O(Ndim) et il faut séparer l'image en hyper-bandes à traîter séparément à cause du coût mémoire (ce qui augmente l'effet linéaire de bord)
* Utiliser un voisinage hexagonal se fait toujours en temps constant

# Résulats

* L'algorithme en O(1) bien plus rapide, et fonctionne bien même quand R petit, car la constante est petite
