# CPP08 — Résumé Détaillé pour la Défense

## Vue d'ensemble : Conteneurs, Itérateurs, Algorithmes
La **STL (Standard Template Library)** est la boîte à outils ultime du développeur C++. Avant le CPP08, tu devais coder tes propres listes chaînées ou tableaux dynamiques. Maintenant, la STL le fait pour toi de manière ultra-optimisée.

| Exercice | Concept clé | Ce qu'il faut retenir |
|:---------|:--------|:------------------|
| ex00 | `<algorithm>` & Iterators | Utiliser `std::find` pour chercher dans n'importe quel conteneur sans se soucier de sa structure interne. |
| ex01 | Conteneurs complexes | Gérer la mémoire, pré-allouer (`reserve()`), et calculer des distances efficacement (`std::sort`, `min_element`). |
| ex02 | *Container Adaptors* | Héritage de `std::stack` pour accéder à son conteneur sous-jacent protégé et "hacker" des itérateurs. |

---

## 1. Conteneurs & Itérateurs (Le Duo Magique)

En C, un tableau est juste un bloc de mémoire. En C++, la notion de stockage est séparée de la notion de parcours.

* **Le Conteneur (`std::vector`, `std::list`, `std::map`...)** s'occupe *uniquement* de ranger la donnée. 
* **L'Itérateur (`iterator`)** s'occupe de parcourir la donnée. 

Un **itérateur** se comporte exactement comme un pointeur. Tu peux faire `it++` pour passer à l'élément suivant et `*it` pour lire la valeur. L'énorme avantage de ce design, c'est que `it++` a toujours l'air simple, mais en coulisses :
- Sur un `vector`, il avance d'une case mémoire (rapide).
- Sur une `list`, il suit le pointeur `next` de ta liste chaînée (un peu plus lent, mais le code reste identique pour toi).

C'est ce qui a permis de résoudre **l'ex00** : on appelle `std::find(container.begin(), container.end(), value)`. Cet algorithme ne se préoccupe pas de savoir si c'est une liste ou un vecteur, il fait juste des `it++` jusqu'à trouver la valeur ou atteindre la fin.

---

## 2. Span : Optimiser la gestion mémoire (ex01)

L'ex01 te demandait de trouver le chemin le plus court ou le plus long entre deux nombres.

### Pourquoi avoir utilisé `std::vector` et pas un `int[]` ?
Le `vector` est un "tableau intelligent". Il gère tout seul la mémoire dynamique (avec `new` et `delete` en interne). 
**L'astuce de la méthode `reserve(N)`** : Un vecteur doit s'agrandir de temps en temps quand il manque de place, ce qui le force à re-copier toute sa mémoire (ce qui ralentit le programme). De base on connait `_maxSize`, alors on utilise `reserve(_maxSize)`. Le vecteur alloue toute la mémoire en une seule fois dès le début. Pour 10 000 éléments, le gain de temps est monumental !

### Algorithmes utilisés
- **`shortestSpan` (Complexité $O(N \log N)$)** : On copie notre vecteur et on utilise `std::sort`. Une fois trié, la valeur mathématiquement la plus proche se trouve forcément sur la case voisine. On trouve le minimum en un seul passage for.
- **`longestSpan` (Complexité $O(N)$)** : On utilise `std::max_element` et `std::min_element` pour vérifier tout le vecteur sans le trier (un seul passage hyper rapide).

---

## 3. MutantStack : Le Container Adaptor Hack (ex02)

### Mais pourquoi l'exercice nous fait faire ça ? Je pensais que c'était plus compliqué !
Oui, tout l'exercice tenait en deux lignes : `return this->c.begin();` !
Le but de l'exercice n'était pas de te faire coder de la grosse logique, mais de **t'enseigner la différence fondamentale entre un vrai conteneur et un *container adaptor***.

Dans la STL, il y a :
1. **Les séquences pures** : vector, list, deque... Elles gèrent de la vraie mémoire.
2. **Les adaptateurs (*Container Adaptors*)** : stack, queue, priority_queue. Elles ne stockent **rien** par elles-mêmes ! 

Une `std::stack` n'est qu'un "parasite" : par défaut, elle s'accroche au dos d'un `std::deque` existant et se contente de restreindre ses droits. 
La `stack` cache exprès les itérateurs du `deque` pour empêcher le programmeur d'aller lire au milieu de la pile (puisqu'une pile, par définition, ne se lit que par en haut).

**Comment as-tu contourné ça ?**
- Tu as créé une classe qui *hérite* de `std::stack`.
- Le standard C++ stipule que la `stack` garde l'accès à son vrai conteneur caché dans une **variable membre protégée nommée `c`**.
- Comme ton `MutantStack` est un enfant, il a le temps d'accéder aux attributs `protected` ! Tu as donc pu taper dans `this->c`, chopper les itérateurs volés, et les redonner librement au monde extérieur (public). 
- C'est un hack d'architecture pur et dur. C'est exactement la leçon que cherche à t'apprendre le CPP08 !

---

## Questions pièges possibles

> **"Qu'est-ce qu'un itérateur ?"**
> C'est un objet (souvent une classe interne) qui se comporte comme un pointeur. Il gère l'avancement "intelligemment" en fonction de la structure du conteneur en dessous (suivre des nœuds pour une list, avancer d'une case mémoire pour un vector).

> **"Pourquoi `std::find` retourne la fin du conteneur quand il ne trouve pas la valeur ?"**
> Car s'il retournait "NULL", ça ferait planter le système typé des itérateurs. Retourner `.end()` est un signal universel qui signifie "je suis sorti des limites du conteneur sans rien trouver".

> **"Qu'est-ce qu'un container adaptor ?"**
> Une classe comme `std::stack` ou `std::queue`. Ce ne sont pas des vrais conteneurs : ils parasitent un autre conteneur (ex: `deque`) et bloquent l'accès à ses fonctions pour forcer une règle ("dernier entré, premier sorti" pour une stack).

> **"Pourquoi utiliser `reserve` sur le vecteur ?"**
> Pour éviter que le `std::vector` doive redimensionner sa mémoire 15 fois en recopiant tous ses éléments. On lui dit précisément combien de cases préparer dès le constructeur, ce qui économise énormément de CPU.

> **"Pourquoi shortestSpan a besoin de trier le tableau, alors que longestSpan a juste besoin de min et max ?"**
> Le plus grand écart possible dans un ensemble de nombres est TOUJOURS la différence entre le plus grand nombre et le plus petit nombre de l'ensemble. Un seul passage avec `min_element` et `max_element` suffit.
> En revanche, le plus PETIT écart possible peut se trouver entre de valeurs n'importe où dans le tableau si on ne le trie pas. Chercher ça sans trier nous obligerait à comparer CHAQUE nombre avec CHAQUE autre nombre (une complexité épouvantable en $O(N^2)$). En triant le vecteur d'abord ($O(N \log N)$), on a la certitude mathématique que les nombres avec le plus petit écart sont devenus voisins. On n'a plus qu'à comparer chaque nombre avec son voisin direct !
