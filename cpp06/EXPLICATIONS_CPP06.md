# CPP06 — Résumé Détaillé pour la Défense

## Vue d'ensemble

Le CPP06 enseigne les **3 types de casts** en C++ :

| Exercice | Cast | Utilité |
|:---------|:-----|:--------|
| ex00 | `static_cast` | Convertir entre types compatibles (int ↔ double ↔ char) |
| ex01 | `reinterpret_cast` | Réinterpréter la mémoire brute (pointeur ↔ entier) |
| ex02 | `dynamic_cast` | Identifier le vrai type d'un objet polymorphique |

### Pourquoi des casts C++ et pas des casts C ?

```cpp
// Cast C — dangereux, aucune vérification
int i = (int)3.14;           // ça marche
char *p = (char *)12345;     // ça compile aussi... mais ça crash

// Casts C++ — chacun a un rôle précis et des vérifications
int i = static_cast<int>(3.14);              // ✅ conversion logique
uintptr_t n = reinterpret_cast<uintptr_t>(ptr);  // ✅ réinterprétation explicite
A *a = dynamic_cast<A *>(base_ptr);          // ✅ vérifié à l'exécution
```

Les casts C++ sont **plus verbeux** exprès — pour qu'on voie clairement qu'il y a une conversion.

---

## Ex00 — ScalarConverter (`static_cast`)

### Classe non-instanciable

```cpp
class ScalarConverter {
    private:
        ScalarConverter();  // ← constructeur PRIVÉ
    public:
        static void convert(const std::string &literal);  // ← STATIC
};
ScalarConverter::convert("42");  // ✅ pas besoin d'objet
ScalarConverter s;               // ❌ constructeur privé
```

**`static`** = la méthode appartient à la **classe**, pas à un objet. Pas besoin de créer une instance.

### Le flux de conversion

```
convert("42.0f")
  → Détecte le type : float (se termine par 'f' et contient '.')
  → Convertit en double : 42.0
  → Affiche dans les 4 types avec static_cast :
      char: '*'   (static_cast<char>(42.0) = '*' car ASCII 42 = *)
      int: 42     (static_cast<int>(42.0) = 42)
      float: 42.0f
      double: 42.0
```

### `static_cast` — Conversion avec vérification du compilateur

```cpp
double d = 42.7;
int i = static_cast<int>(d);      // → 42 (tronque la partie décimale)
char c = static_cast<char>(42);   // → '*' (ASCII 42)
```

Le compilateur vérifie que la conversion a du sens. `static_cast<int>("hello")` → erreur de compilation.

### Fonctions de parsing utilisées

| Fonction | Rôle |
|---|---|
| `strtod(str, &end)` | string → double. `end` pointe vers le premier caractère non-converti |
| `strtol(str, &end, 10)` | string → long (base 10) |
| `std::isnan(v)` | `true` si v est NaN (Not a Number) |
| `std::isinf(v)` | `true` si v est infini (+inf ou -inf) |

---

## Ex01 — Serializer (`reinterpret_cast`)

### Le concept

Convertir un **pointeur** (adresse mémoire) en **nombre**, et vice-versa :

```cpp
Data *ptr = new Data();
// ptr = 0x7FFF1234 (une adresse)

uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);
// raw = 140734837284 (la même adresse, mais comme un nombre)

Data *back = reinterpret_cast<Data *>(raw);
// back = 0x7FFF1234 (retour au pointeur)
// ptr == back → true ✅
```

### `reinterpret_cast` vs `static_cast`

```cpp
// static_cast → CONVERTIT la valeur (change les bits si nécessaire)
double d = 42.7;
int i = static_cast<int>(d);  // i = 42 (les bits changent)

// reinterpret_cast → RÉINTERPRÈTE les bits (aucun changement)
Data *ptr = ...;
uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);  // mêmes bits, lecture différente
```

### `uintptr_t`

Un entier non-signé assez grand pour stocker n'importe quelle adresse mémoire (défini dans `<stdint.h>`).

---

## Ex02 — Identify (`dynamic_cast`)

### Le concept

Quand tu as un `Base *` qui peut être A, B, ou C, `dynamic_cast` vérifie le **vrai type** à l'exécution :

### Par pointeur — retourne NULL si échec

```cpp
Base *ptr = generate();  // on ne sait pas le type

if (dynamic_cast<A *>(ptr))       // est-ce un A ?
    std::cout << "A";
else if (dynamic_cast<B *>(ptr))  // est-ce un B ?
    std::cout << "B";
else if (dynamic_cast<C *>(ptr))  // est-ce un C ?
    std::cout << "C";
```

### Par référence — throw une exception si échec

```cpp
try {
    A &a = dynamic_cast<A &>(ref);  // essaie de caster en A&
    std::cout << "A";               // si on arrive ici, c'est un A
}
catch (...) {                       // si ce n'est pas un A, on essaie B...
}
```

Avec les pointeurs → retourne `NULL`. Avec les références → `throw` (car une référence ne peut pas être NULL).

### Pourquoi `catch(...)` et pas `catch(std::bad_cast)` ?

Le sujet **interdit** `#include <typeinfo>`. Or `std::bad_cast` est défini dans ce header. `catch(...)` attrape **n'importe quelle** exception.

---

## Résumé des 3 casts

| Cast | Quand l'utiliser | Vérifié quand ? |
|---|---|---|
| `static_cast` | Conversions entre types compatibles (int↔double, char↔int) | À la **compilation** |
| `reinterpret_cast` | Réinterpréter la mémoire brute (pointeur↔entier) | **Jamais** (dangereux, à utiliser avec précaution) |
| `dynamic_cast` | Identifier le vrai type dans un héritage polymorphique | À l'**exécution** (runtime) |

## Questions pièges possibles

> **"Pourquoi le constructeur de ScalarConverter est privé ?"**
> Pour rendre la classe non-instanciable. On n'a besoin que de la méthode statique `convert()`, pas d'un objet.

> **"Pourquoi static sur la méthode convert ?"**
> Une méthode `static` n'a pas besoin d'objet pour être appelée. On fait `ScalarConverter::convert()` directement.

> **"Quelle est la différence entre static_cast et un cast C ?"**
> `static_cast` est vérifié par le compilateur — il refuse les conversions absurdes. Le cast C `(int)ptr` accepte tout sans vérification.

> **"Pourquoi reinterpret_cast est dangereux ?"**
> Il ne vérifie rien du tout. Si tu cast un `int *` en `double *`, le programme compilera mais crashera probablement.

> **"Pourquoi dynamic_cast a besoin d'un destructeur virtual ?"**
> `dynamic_cast` utilise la vtable (table des fonctions virtuelles) pour identifier le type réel. Sans `virtual`, il n'y a pas de vtable → `dynamic_cast` ne fonctionne pas.

> **"C'est quoi le 4ème cast C++ que tu n'as pas utilisé ?"**
> `const_cast` — sert à ajouter ou retirer le `const` d'une variable. Rarement utilisé.
