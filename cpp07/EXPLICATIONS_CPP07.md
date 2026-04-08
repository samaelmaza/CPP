# CPP07 — Résumé Détaillé pour la Défense

## Vue d'ensemble

Le CPP07 nous introduit au monde puissant des **templates** (modèles) en C++. L'idée centrale est la **programmation générique** : écrire un seul bout de code qui peut fonctionner avec une infinité de types de données.

| Exercice | Concept clé | Utilisation typique |
|:---------|:--------|:------------------|
| ex00 | **Function templates** classiques | Fonctions utilitaires comme swap, min, max |
| ex01 | **Fonctions en paramètres** + templates | Appliquer une fonction sur tout un tableau |
| ex02 | **Class templates** | Créer des conteneurs génériques (comme les vecteurs) |

---

## 🔑 La théorie des Templates

En C, si tu voulais une fonction `swap` pour des `int` et une autre pour des `double`, tu devais écrire deux fonctions. Si tu utilisais `void *`, tu perdais la sécurité du type (risque de segfault/comportement indéfini).

En C++, grâce aux templates :
```cpp
template <typename T>
void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
```

**Que se passe-t-il quand tu compiles ?**
Le compilateur voit ton code, regarde avec quels types tu as appelé `swap` (par exemple `int` et `std::string`), et **génère automatiquement** deux fonctions invisibles dans ton binaire :
- Une fonction `swap` où `T` est remplacé par `int`
- Une fonction `swap` où `T` est remplacé par `std::string`

 C'est pour ça qu'on dit "template" (modèle) : c'est un patron à partir duquel le compilateur fabrique les vraies fonctions.

### Ligne obligatoire : `template <typename T>`
On doit mettre `template <typename T>` au-dessus de **chaque** déclaration ou définition de fonction template. 
*(On peut aussi utiliser `template <class T>`, c'est exactement la même chose).*

---

## Ex00 — Quelques fonctions simples (swap, min, max)

Cet exercice est l'introduction basique. On crée des fonctions qui prennent des paramètres par référence :

### Swap
```cpp
template <typename T>
void swap(T &a, T &b) { ... }
```
Prend par référence `&` car on veut modifier les variables originales (`a` et `b`).

### Min / Max
```cpp
template <typename T>
T const &min(T const &a, T const &b) { ... }
```
Prend `T const &` (référence constante) car on ne veut **pas** modifier les valeurs, et on ne veut **pas** faire une copie inutile (si `T` est une grosse string par exemple). Le retour est aussi `T const &` pour renvoyer la valeur sélectionnée sans la copier.

---

## Ex01 — Iter (Parcourir un tableau générique)

Ici on va un peu plus loin : on passe non seulement un tableau générique (`T *`), mais aussi une fonction (`F`) en paramètre.

```cpp
template <typename T, typename F>
void iter(T *array, size_t length, F func) {
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}
```

### Pourquoi `typename F` ?
En utilisant `F` pour la fonction, `iter` peut accepter :
- Des pointeurs sur fonctions classiques (ex: `void myFunction(int &x)`)
- Des pointeurs sur d'autres fonctions templates (ex: `print<int>`)

L'avantage, c'est qu'on a fait une fonction universelle qui peut tout faire sur un tableau : afficher les éléments, les mettre en majuscule, les multiplier... sans jamais réécrire la boucle `for` !

---

## Ex02 — Array (Class Templates)

C'est l'exercice le plus complexe. On crée notre propre conteneur, un peu comme un `std::vector` hyper basique.

### Comment définir une classe template ?
```cpp
template <typename T>
class Array {
    private:
        T *_array;
        unsigned int _size;
    ...
};
```

Il y a une grande règle à respecter avec les classes template : **Toutes les méthodes doivent être visibles par le compilateur au moment où il crée l'objet**.  
C'est pour ça qu'il ne faut **pas** mettre les implémentations dans un fichier `.cpp` ! Habituellement on les met dans un `.tpp` (Template Plus Plus) ou `.ipp` qu'on `#include` à la fin du `.hpp`.

### Les détails cruciaux de l'implémentation :

1.  **L'allocation (`new T[n]()`)** :
    ```cpp
    Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n) {}
    ```
    Le `()` à la fin de `new T[n]()` est très important ! Il demande au compilateur de faire une **initialisation par défaut**.
    - Si `T` est `int`, le tableau sera rempli de `0`.
    - Si `T` est un objet (ex: `std::string`), le constructeur par défaut de cet objet sera appelé.

2.  **Copie Profonde (Deep Copy)** :
    Comme d'hab (OCF !), puisqu'on utilise `new` (mémoire dynamique), le constructeur par copie et l'opérateur d'assignation `=` doivent :
    1. Allouer un nouveau tableau de la bonne taille.
    2. Copier chaque élément avec une boucle.
    *(Si on ne le faisait pas, on copierait juste le pointeur interne et modifier l'un modifierait l'autre, et le delete[] final exploserait en double free).*

3.  **L'opérateur `[]`** :
    ```cpp
    template <typename T>
    T &Array<T>::operator[](unsigned int index) {
        if (index >= this->_size)
            throw std::exception(); // Out of bounds !
        return this->_array[index];
    }
    ```
    C'est le gros point fort de notre Array par rapport à un tableau classique `int tab[10]`. Si on fait `tab[15]`, c'est un undefined behavior (souvent un Segfault très tardif et dur à trouver). Notre classe `Array` **throw une exception instantanément**. C'est très sécurisé.

---

## Questions pièges possibles

> **"Que se passe-t-il si je compile ce code, mon exécutable va être lourd car il y a tous les types possibles gérés ?"**
> Faux. Le binaire contiendra **uniquement** les versions de la fonction/classe avec les types que tu as *réellement* utilisés dans ton `main`. Le compilateur crée à la demande.

> **"Pourquoi les fichiers .hpp et .tpp et pas .cpp pour les templates ?"**
> Le compilateur a besoin du code source de l'implémentation pour pouvoir créer la fonction/classe avec le bon type quand il la rencontre. Si le code est dans un `.cpp` déjà compilé, il ne peut pas « générer » le code pour le nouveau type.

> **"Dans Ex02, pourquoi y a-t-il deux `operator[]` (un normal, un const) ?"**
> Si je passe mon `Array` dans une fonction comme `const Array<int> &tab`, l'objet devient constant. Si je n'avais pas la méthode `operator[] const`, le compilateur m'interdirait de lire `tab[0]` car il aurait peur que je le modifie. Avoir la version `const` permet la lecture sans modification.
