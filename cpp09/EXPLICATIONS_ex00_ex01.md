# 📚 Guide de Survie & Défense : BitcoinExchange (ex00) & RPN (ex01)

Tout comme pour l'algorithme Ford-Johnson, ce document rassemble toutes les explications et les questions pièges récurrentes en soutenance pour les exercices 00 et 01 du module C++09.

---

# 🪙 EX00 : BitcoinExchange (btc)

L'objectif de cet exercice est d'utiliser un conteneur (**std::map**) pour faire une association `Date => Valeur`. Ensuite, tu dois calculer la valeur d'un portefeuille à des dates données.

## 🧐 1. Explication du Code

### Le fonctionnement de `std::map::lower_bound`
C'est **LA** fonction la plus importante de cet exercice. Elle se trouve dans ta méthode `getExchangeRate` :

```cpp
std::map<std::string, double>::const_iterator it = _db.lower_bound(date);

if (it != _db.end() && it->first == date)
    return it->second; // Date exacte trouvée !

if (it == _db.begin())
    return 0.0; // La date demandée est plus ancienne que les débuts du bitcoin

--it; // On recule d'un cran pour trouver la date la plus proche DANS LE PASSÉ
return it->second;
```

**Pourquoi ceci marche ?**
* L'itérateur de la `map` trie *automatiquement* les dates dans l'ordre chronologique (car une string `"2011-01-01"` est alphabétiquement inférieure à `"2012-01-01"`).
* `lower_bound(date)` trouve le **premier élément qui n'est pas strictement inférieur** à la date fournie.
* Si on demande `"2012-01-15"`, et que la base a la date *"2012-01-14"* et *"2012-01-17"*.
* `lower_bound` nous pointera sur `"2012-01-17"` !
* C'est pour ça qu'on fait `--it;`. Cela nous fait reculer sur la date la plus proche **dans le passé**, soit `"2012-01-14"`.

### La validation des Dates (`isValidDate`)
La logique de validation gère tout : la taille, la présence des `-`, et surtout gère **les années bissextiles** :
```cpp
int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
    daysInMonth[1] = 29; // Remplace Février (28 -> 29)
```

## 🕵️‍♂️ 2. Questions Pièges en Soutenance (EX00)

> [!CAUTION]
> **Q : Quel conteneur as-tu utilisé et pourquoi ?**
> R : J'ai utilisé `std::map`. Le `std::map` est un arbre binaire de recherche (Red-Black tree) qui garde ses éléments triés automatiquement par clé (la date). C'est parfait ici car je peux faire appel à `lower_bound()` pour la recherche de dates avec une complexité logarithmique en **O(log n)**, beaucoup plus rapide que chercher dans un simple Vector de paire.

> [!CAUTION]
> **Q : Que se passe-t-il si j'écris la date : 2022-02-29 ?**
> R : Mon programme va le bloquer. L'année 2022 n'est pas bissextile (elle n'est pas divisible par 4), donc `daysInMonth[1]` (le mois de février) reste à 28. Mon algo rejettera le jour 29.

> [!CAUTION]
> **Q : As-tu géré max overflow pour la valeur du bitcoin ?**
> R : Le sujet spécifiait qu'un *value* lu doit être tenu dans un `float` ou un `int` entre 0 et 1000. Par contre, le résultat final du calcul peut dépasser. Mon parsing gère le `double` (via `strtod`) pour être sécurisé.

---

# 🧮 EX01 : RPN (Reverse Polish Notation)

Le but est d'écrire un petit calculateur en s'appuyant sur l'utilisation du conteneur **std::stack** (la pile).
Dans la notation polonaise inverse, le concept est que **l'opérateur arrive APRES les chiffres**. Ex: `3 4 +` donne 7.

## 🧐 1. Explication du Code

### Le découpage via `std::stringstream`
```cpp
std::stringstream ss(expression);
std::string token;
while (ss >> token)
```
Le `std::stringstream` permet d'isoler (tokéniser) l'entrée pour lire entre chaque bloc d'espace. Ainsi avec `"3 4 +"`, l'itération lira `3`, puis `4`, puis `+`.

### Le concept "LIFO" de la std::stack
La `stack` (pile) fonctionne en mode _LIFO (Last In, First Out)_. Le dernier rentré est le premier sorti.
```cpp
int b = _stack.top();
_stack.pop();
int a = _stack.top();
_stack.pop();
```
* **Attention à l'ordre !** Comme on dépile, le premier chiffre qui sort (`b`) est le chiffre de **droite** de l'opération, et le second (`a`) est celui de **gauche**.
* Exemple sur `"5 2 /"` : Le 2 sort en premier (donc `b = 2`), puis le 5 sort (`a = 5`). L'opération finale est bien `5 / 2`.
* Si je n'avais pas sauvé cet ordre inverse, le code aurait calculé `2 / 5`.

## 🕵️‍♂️ 2. Questions Pièges en Soutenance (EX01)

> [!CAUTION]
> **Q : Le sujet interdit qu'on utilise un nombre d'un certain chiffre ?**
> R : Le sujet spécifie que chaque chiffre (*digit*) ne peut être que de gauche à 9 au maximum, pas `10` ou plus. Dans mon code, je vérifie `token.size() != 1` : n'importe quel double chiffre comme `15` provoquera une throw d'invalidité. C'est strict au charactère !

> [!CAUTION]
> **Q : Quel conteneur tu as choisi et pourquoi ?**
> R : J'ai utilisé `std::stack`, car le comportement naturel d'un interpréteur de Notation Polonaise Inverse fonctionne avec un ordre **LIFO**. À chaque itération de la ligne d'expression on stocke ce qu'il faut *en empilant* et l’on résout quand un opérateur tombe *en dépilant*. `std::stack` est un _container adapter_. En interne, c'est généralement construit sur un `std::deque` par défaut, mais masquer son utilisation permet d'empêcher les accès bizarres au milieu du tableau et garder la sécurité conceptuelle d'une pile.

> [!CAUTION]
> **Q : Comment ton programme gère-t-il `5 0 /` ?**
> R : Mon programme lance une `runtime_error` que j'ai attrapé pour éviter de faire un "_Division by zero_" (Floating point exception) qui ferait crasher violemment le module. C'était spécifiquement géré par la condition `if (b == 0) throw std::runtime_error("Error: division by zero");`.
