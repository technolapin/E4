# Cours 1: Programation DLX
 prof: Thierry Grandpierre

## Architecture Load/Store


Un ordinateur “minimal” a besoin:

* D'un Processeur
* D'une RAM
* d'une horloge
* d'une ROM/Flash

![](ordinateur_minimal.jpg)

L'architecture RISC rend obligatoire de stocker les données à modifier en registre, ce qui fait perdre quelques cycles d'horloges, mais rend ensuite les opérations sur ces valeurs en registres très rapide. C'est l'architecture Load/Store.


L'unité responsable des opérations logiques et arithmétiques est l'ALU (Arithmetic and Logic Unit)
L'ALU a deux entrées de données, une de contrôle (pour le choix de l'opération) et une sortie.

![](alu.jpg)

## Les 3 formats d'instruction: I, R, J (taille 32bits)

### Rappels des instructions DLX

1. Data Transfert - Accès mémoire
2. Arithmétique et logique
3. Control
4. Floating Point

Les opérations d'accès mémoire et de transferts de données sont par exemple LOAD et STORE

Les opérations Arithmétiques et logiques sont celles relevant de L'ALU

Les opérations de contrôle sont celles permettant de modifier la ligne du code pointée, comme dans un GOTO, un IF ...

Les opérations sur les flottants peuvent être décomposées en plusieures opérations sur les entiers, ce qui les rend plus lentes à traîter.
Elles relève d'une unitée FPU (Float Point Unit) ou de l'ALU s'il n'y en a pas.

## 32 registres d'usage général

R0 vaut toujours 0 (ce qui permet de toujours avoir un 0 sous la main)
