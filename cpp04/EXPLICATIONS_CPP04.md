# CPP04 — Explications Détaillées

## Vue d'ensemble

Le CPP04 est centré sur le **polymorphisme** et les **classes abstraites/interfaces** en C++. Chaque exercice introduit un concept clé :

| Exercice | Concept principal |
|:---------|:------------------|
| ex00 | Polymorphisme de base (`virtual`) |
| ex01 | Deep copy vs Shallow copy (avec `Brain`) |
| ex02 | Classes abstraites (fonctions virtuelles pures `= 0`) |
| ex03 | Interfaces (`ICharacter`, `IMateriaSource`) |

---

## 1. 🎭 Ex00 — Le Polymorphisme (`virtual`)

### Le problème : sans `virtual`

C'est exactement le piège montré par `WrongAnimal` / `WrongCat` :

```cpp
// WrongAnimal.hpp
class WrongAnimal {
    void makeSound() const;         // PAS virtual !
};

// Animal.hpp
class Animal {
    virtual void makeSound() const; // ← VIRTUAL
};
```

Quand on utilise un **pointeur de type parent** vers un **objet enfant** :

```cpp
const Animal* i = new Cat();
i->makeSound();   // → affiche le son du CHAT ✅ (grâce à virtual)

const WrongAnimal* wrong = new WrongCat();
wrong->makeSound(); // → affiche le son de WrongANIMAL ❌ (pas virtual)
```

### Pourquoi ?

- **Sans `virtual`** : C++ regarde le **type du pointeur** (WrongAnimal*) et appelle la méthode de WrongAnimal. C'est du **binding statique** (décidé à la compilation).
- **Avec `virtual`** : C++ regarde le **type réel de l'objet** (Cat) et appelle la bonne méthode. C'est du **binding dynamique** (décidé à l'exécution, via la **vtable**).

### Le destructeur virtuel est OBLIGATOIRE

```cpp
class Animal {
    virtual ~Animal();  // ← IMPORTANT !
};
```

Sans `virtual` sur le destructeur, quand on fait `delete` sur un `Animal*` qui pointe vers un `Dog`, seul le destructeur de `Animal` serait appelé. Le destructeur de `Dog` (qui doit `delete` le `Brain`) ne serait **jamais appelé** → **fuite mémoire** !

---

## 2. 🧠 Ex01 — Deep Copy vs Shallow Copy

### Le problème

`Dog` et `Cat` ont maintenant un attribut `Brain*` alloué dynamiquement :

```cpp
class Dog : public Animal {
    private:
        Brain *_brain;  // ← pointeur vers un objet alloué avec new
};
```

### Shallow Copy (copie superficielle) — LE DANGER ⚠️

Si on copie juste le pointeur :
```cpp
Dog a;
Dog b = a;  // b._brain = a._brain → MÊME adresse !
```

Les deux chiens partagent le **même** `Brain` en mémoire :
- Si on modifie `b._brain->ideas[0]`, ça modifie aussi `a._brain->ideas[0]`
- Quand `a` est détruit, il fait `delete _brain`
- Quand `b` est détruit, il fait AUSSI `delete _brain` → **double free** 💥

### Deep Copy (copie profonde) — LA SOLUTION ✅

On alloue un **nouveau** `Brain` et on copie le **contenu** :

```cpp
// Constructeur de copie
Dog::Dog(const Dog &src) : Animal(src) {
    this->_brain = new Brain(*src._brain);  // ← nouveau Brain, contenu copié
}

// Opérateur d'assignation
Dog &Dog::operator=(const Dog &rhs) {
    Animal::operator=(rhs);
    delete this->_brain;                     // ← libérer l'ancien
    this->_brain = new Brain(*rhs._brain);   // ← allouer un nouveau
    return *this;
}
```

Maintenant chaque `Dog` a son **propre** `Brain`, indépendant.

### Règle d'or

> Dès qu'une classe a un **pointeur** comme attribut, il FAUT implémenter la **deep copy** dans le constructeur de copie ET l'opérateur d'assignation. C'est la **Rule of Three** en C++.

---

## 3. 🚫 Ex02 — Classes Abstraites (Fonctions Virtuelles Pures)

### Le concept

On ajoute `= 0` à la fin d'une méthode virtuelle pour la rendre **pure** :

```cpp
class Animal {
    virtual void makeSound() const = 0;   // ← PURE VIRTUAL
};
```

### Conséquences

1. **`Animal` devient une classe abstraite** — on ne peut PLUS faire `Animal a;` ni `new Animal()`. C'est une erreur de compilation.
2. **Toutes les classes enfants DOIVENT implémenter `makeSound()`**, sinon elles sont aussi abstraites.
3. Le reste du code (tableaux de `Animal*`, polymorphisme, etc.) fonctionne **exactement pareil**.

### Pourquoi c'est utile ?

Parce que créer un `Animal` générique n'a **aucun sens**. Quel son fait un "animal" ? Rien de concret. En le rendant abstrait, on **force** les enfants à définir leur comportement, et on empêche l'instanciation d'un concept trop vague.

---

## 4. 📜 Ex03 — Interfaces (le vrai patron de conception)

### Interface vs Classe Abstraite

| | Classe Abstraite (`AMateria`) | Interface (`ICharacter`, `IMateriaSource`) |
|---|---|---|
| Peut avoir des attributs ? | ✅ Oui (`_type`) | ❌ Non |
| Peut avoir du code dans les méthodes ? | ✅ Oui | ❌ Non (que des `= 0`) |
| Préfixe convention 42 | `A` (Abstract) | `I` (Interface) |

### `ICharacter` — L'interface

```cpp
class ICharacter {
    public:
        virtual ~ICharacter() {}
        virtual std::string const &getName() const = 0;  // = 0 partout
        virtual void equip(AMateria *m) = 0;
        virtual void unequip(int idx) = 0;
        virtual void use(int idx, ICharacter &target) = 0;
};
```

C'est un **contrat pur** : "si tu veux être un ICharacter, tu DOIS implémenter toutes ces fonctions". Pas d'attributs, pas de code, que des signatures.

### `AMateria` — La classe abstraite

```cpp
class AMateria {
    protected:
        std::string _type;              // ← a un attribut
    public:
        virtual AMateria *clone() const = 0;  // ← pure virtual (abstraite)
        virtual void use(ICharacter &target);  // ← a du code par défaut
};
```

Elle est à mi-chemin : elle a des attributs et du code, mais elle a aussi une méthode pure virtuelle (`clone()`), donc on ne peut pas l'instancier directement.

### `Character` — L'implémentation concrète

```cpp
class Character : public ICharacter {
    private:
        std::string _name;
        AMateria *_inventory[4];  // ← inventaire de 4 matérias
};
```

`Character` implémente TOUTES les méthodes de `ICharacter` → elle est **concrète**, on peut faire `new Character("Cloud")`.

### Pourquoi des interfaces ?

Les interfaces permettent de coder **contre une abstraction** plutôt que contre une implémentation concrète. Par exemple, une fonction qui prend un `ICharacter&` accepte N'IMPORTE QUELLE classe qui implémente `ICharacter`, pas seulement `Character`. Ça rend le code extensible sans le modifier.

---

## Résumé des concepts clés du CPP04

```
virtual          → Polymorphisme (binding dynamique)
virtual ~        → Destructeur virtuel (évite les fuites mémoire)
= 0              → Fonction virtuelle pure (force l'implémentation)
Classe abstraite → Au moins une méthode = 0, ne peut pas être instanciée
Interface        → QUE des méthodes = 0, aucun attribut, contrat pur
Deep copy        → Allouer + copier le contenu (pas juste copier le pointeur)
```
