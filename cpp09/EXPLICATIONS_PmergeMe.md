# 📚 Guide de Survie & Défense : PmergeMe (Ford-Johnson)

Ce document a été spécialement conçu pour t'aider à réussir ta soutenance (défense) pour l'exercice 02 du module CPP09. Il couvre la théorie, l'explication du code ligne par ligne, et les questions pièges posées par les évaluateurs.

---

## 🎯 1. Concept de l'algorithme (Merge-Insert Sort)

L'algorithme de Ford-Johnson (Merge-Insert Sort) a un but unique et très spécifique : **trier une collection en faisant le moins de comparaisons possibles entre les éléments**.

> [!WARNING]
> **Ce n'est pas l'algorithme le plus rapide en terme d'exécution !**
> L'évaluateur va sûrement te demander : *"Est-ce que cet algorithme est rapide ?"*
> Ta réponse : *"Non, en pratique sur un processeur moderne, un QuickSort ou un simple std::sort est beaucoup plus rapide. Mais cet algo est conçu pour minimiser le nombre de comparaisons mathématiques (si comparer coûtait très cher, ex: trier d'immenses bases de données, cet algorithme serait intéressant)."*

---

## 🧐 2. Explication Ligne par Ligne de `_sortVector`

Voici ton code divisé en étapes avec des explications simples pour chaque ligne clé.

### Étape 0 : Base Case (Sortie rapide)
```cpp
if (vec.size() <= 1)
    return;
```
Si le vecteur est vide ou n'a qu'un seul élément, il est déjà trié. C'est surtout crucial car `_sortVector` va s'appeler de manière récursive.

### Étape 1 : Gestion de l'impair et création des Paires
```cpp
bool hasStraggler = (vec.size() % 2 != 0);
int straggler = -1;
if (hasStraggler) {
    straggler = vec.back(); // Met l'élément de côté
    vec.pop_back();         // Le retire du vecteur principal
}

std::vector<std::pair<int, int> > pairs;
for (size_t i = 0; i < vec.size(); i += 2) {
    if (vec[i] > vec[i + 1])
        pairs.push_back(std::make_pair(vec[i], vec[i + 1])); // Winner, Loser
    else
        pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
}
```
* **Objectif** : Placer les éléments par paires et déterminer qui "gagne" (le plus grand) et qui "perd" (le plus petit).
* **Attention** : `first` de la pair contient **toujours** le vainqueur. L'élément de côté (straggler) attendra la toute fin de l'algorithme.

### Étape 2 : Récursion sur les gagnants
```cpp
std::vector<int> winners;
for (size_t i = 0; i < pairs.size(); ++i)
    winners.push_back(pairs[i].first); // Extraction des gagnants

_sortVector(winners); // Récursion magique !
```
À cette étape, on prend tous nos éléments "gagnants" et on rappelle la fonction pour qu'ils se trient avec la même logique. Lorsqu'on passe à la ligne suivante, `winners` est **entièrement trié**.

### Étape 3 : Retrouver les perdants (pend)
```cpp
std::vector<int> pend;
for (size_t i = 0; i < winners.size(); ++i) {
    for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        if (it->first == winners[i]) {
            pend.push_back(it->second);
            pairs.erase(it);
            break;
        }
    }
}
```
* **Pourquoi on fait ça ?** Maintenant que nos gagnants ont bougé, nous devons aligner nos perdants (`pend`) dans le **même ordre**.
* **Pourquoi `erase()` ?** S'il y a des nombres en doubles (ex: deux fois le chiffre `4` dans les gagnants), le premier `4` prendra son perdant et s'effacera de la liste de recherche pour éviter que le second `4` ne prenne le même perdant.

### Étape 4 & 5 : La chaîne principale et le premier perdant
```cpp
std::vector<int> mainChain = winners;
if (!pend.empty()) {
    mainChain.insert(mainChain.begin(), pend[0]);
}
```
* `mainChain` est notre liste triée finale en construction (elle démarre avec les winners).
* **Magie absolue de l'algo :** Le premier perdant `pend[0]` a perdu contre `mainChain[0]`. Mathématiquement, il a affronté le plus petit des gagnants, donc il est forcément le plus petit élément global ! On l'insère sans **aucune** comparaison au début.

### Étape 6 : L'insertion via Jacobsthal
```cpp
size_t pendSize = pend.size();
if (pendSize > 1) {
    int k = 3;
    size_t prevJac = 1; 
    size_t currJac = _jacobsthal(k); // Retourne 3
...
```
* **Suite de Jacobsthal** : C'est pour minimiser la zone dans laquelle `std::lower_bound` fait sa recherche. La recherche dichotomique coupe en deux, il est alors plus optimal d'utiliser de l'espace de taille (2^n - 1).

```cpp
while (prevJac < pendSize) {
    size_t end = std::min(static_cast<size_t>(currJac), pendSize);
    
    // Boucle à L'ENVERS (de end vers prevJac)
    for (size_t i = end; i > prevJac; --i) {
        int loserToInsert = pend[i - 1]; 
        
        // binary search pour trouver l'emplacement
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), loserToInsert);
        mainChain.insert(pos, loserToInsert);
    }
    // Avance la suite de jacobsthal
    prevJac = currJac;
    k++;
    currJac = _jacobsthal(k);
}
```
* On insère les perdants restants **de droite à gauche** par paquets définis par les nombres de Jacobsthal (les paquets font des tailles de 2, puis 4, puis 10, etc.).

### Étape 7 : Rapatrier l'orphelin (Straggler)
```cpp
if (hasStraggler) {
    std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
    mainChain.insert(pos, straggler);
}
vec = mainChain; // Remplacement final !
```
Si on avait un chiffre tout seul en étape 1, on l'incruste dans la chaîne via une recherche binaire. On assigne la chaîne finie au vecteur passé par référence. Fini !

---

## ⏱️ 3. Processus de temps (`clock()`)

Dans la méthode `run()`, nous testons la vitesse pour notre std::vector et notre std::deque `_sortDeque` :
```cpp
clock_t startVec = clock();
_sortVector(_vec);
clock_t endVec = clock();
double timeVec = (double)(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;
```
* `clock()` renvoie un nombre de *"ticks"* d'horloge cpu.
* La soustraction donne la durée en ticks.
* `CLOCKS_PER_SEC` nous permet de convertir ces ticks en secondes.
* On multiplie par `1000000.0` pour afficher au standard microsecondes (comme demande le sujet).

---

## 🕵️‍♂️ 4. Questions Pièges en Soutenance (Q&A)

### Q : Quelle est la différence entre std::vector et std::deque sous le capot ?
**R :** Le vector alloue **un seul gros bloc contigu** en mémoire (comme un tableau C). S'il manque de place, il réalloue tout ailleurs. Le deque (Double-Ended Queue) alloue des "chunks" (des petits tableaux séparés en mémoire mais liés les uns aux autres par un catalogue central). Ceci permet au deque de rajouter/supprimer super rapidement au début via `push_front()`.

### Q : Si le `push_front()` est génial sur le Deque, pourquoi le vector est souvent plus ou moins aussi rapide (voir plus rapide) dans nos tests ?
**R :** L'algorithme de Ford-Johnson fait énormément de recherches mémoire itératives. Le CPU (processeur) moderne dépend massivement du *Cache*. Vu que le vector possède une **mémoire 100% contiguë**, la lecture transversale en boucle pour la recherche de losers est plus efficace pour lui que pour une double-linked-chunk queue comme le deque. Ça compense le petit retard de l'insertion `insert(begin())` de pend[0].

### Q : Que fait exactement `std::lower_bound` ? Quelle est sa complexité ?
**R :** `std::lower_bound` fait une *binary search* (recherche dichotomique) dans un container trié pour trouver l'emplacement précis d'insertion sans détruire l'ordre. Il divise par deux (coupe l'arbre), regarde la target, divise encore en deux, etc. Sa complexité algorithmique est **O(log n)**. C'est l'essence même de l'étape "Merge-Insert" pour baisser les temps de comparaison.

### Q : Est-ce qu'on aurait pu utiliser std::list pour Ford Johnson ?
**R :** Ce serait un cauchemar total. `std::list` n'autorise pas l'accès aléatoire (*Random Access*). On ne peut pas faire `list[5]`. La fonction `std::lower_bound` serait forcée d'avancer case par case (`iterator++`), ce qui transforme le temps O(log n) en temps désastreux de **O(n)**. L'intérêt théorique de Ford-Johnson serait tué dans l'œuf.

---
Tu gères ! Relis bien ça avant l'évaluation et tu passeras sans encombre. Good luck ! 🚀
