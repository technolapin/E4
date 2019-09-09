>> gros blanc car arrivé en retard

   “si B_H pas défini, alors définir B_H et faire des trucs”
#ifndef B_H
#define B_H
// des trucs

#endif



#pragma once




Quand on utilise qu'un ou deux types d'un fichier .h, on peut utiliser
la déclaration forward.
Ie, faire

 ``` C
 struct S;
 ```



## Pour les constantes

Ne jamais utiliser de #define pour des constantes utilisées dans le code.
Ne jamais rendre les paramètres des fonctions constants


## Site à retenir

https://en.cppreference.com/w/

# Le C++

## Les vecteurs

std::vector<T>
Des vecteurs comme en Rust.

## L'inférence de type

auto i = 0; L'inférence de type.
* DE L'INFÉRENCE DE TYYYPE YEEES *
Bien pour éviter la répétition de code (on n'a pas à écrire tout le temps le type)
et pour éviter d'avoir à écrire un type de 300 caractères à chaque déclaration
de variable.

On peut ajouter `const` et `&` (cf références) à auto

ex:
```C
auto j1 = jumbo(10);
auto j2 = j1; // deep-copy
auto& j3 = j1; // mutable alias
const auto& j4 = j1; // immutable alias
```
NB: si le type inféré est déjà une référence, l'esperluette ajoutée à auto ne s'applique pas.

## typedef

Il ne faut pas utiliser `typedef` en C++, on utilise `using` à la place

## les enums

En C, une enum c'est grosso modo un int.
En C++, on peut écrire
```C
enum class month
{
	january,
	february,
	...
}
```

## les valeurs par défaut

```C
int succ(int i, int delta = 1)
{
	return i+delta;
}
```

À éviter de suritiliser. 

## Les références

Une référence, c'est comme un pointeur, mais qui pointe vers un unique objet bien défini, et qui ne peut pointer vers autre chose.

Éviter de retourner une référence (problème de lifetime, eh oui on est pas en rust)
Préférer retourner un pointeur alloué dynamiquement.


## Les classes

Une classe doit fournir un service.

Les membres privés de la classes sont notés par convention avec un underscore à la fin ou un m_ devant
ex:
```C
class circle
{
public:
	//...
	void translate(float dx, float dy);
	void print() const;
private:
	float x_, y_, r_;
};
```
Les classes, c'est comme les structs, mais avec tous ses champs privés par défaut.

### Les constructeurs

* nommé après la classe
* non-constant
* est une procédure