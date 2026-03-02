# CPP03 — Explications Détaillées

## 1. 🔒 `private` vs `protected`

Les deux sont des **niveaux d'accès** qui empêchent le monde extérieur d'accéder aux attributs, mais ils diffèrent sur un point crucial — **l'héritage** :

|                                         | `private`  | `protected`  |
|:----------------------------------------|:-----------|:-------------|
| Accessible depuis la classe elle-même ? | ✅ Oui     | ✅ Oui       |
| Accessible depuis les **classes enfants** ? | ❌ **Non** | ✅ **Oui** |
| Accessible depuis l'extérieur ?         | ❌ Non     | ❌ Non       |

### Concrètement dans le code

Dans `ClapTrap.hpp` (ex03), les attributs sont en **`protected`** :
```cpp
protected:
    std::string _name;
    unsigned int _hitPoints;
    unsigned int _energyPoints;
    unsigned int _attackDamage;
```

Ça veut dire que `ScavTrap`, `FragTrap`, et `DiamondTrap` peuvent **directement accéder** à `_name`, `_hitPoints`, etc. C'est pour ça que dans `FragTrap.cpp` on peut écrire :
```cpp
this->_hitPoints = 100;    // ✅ Possible car protected
this->_attackDamage = 30;  // ✅ Possible car protected
```

**Si c'était `private`**, ces lignes ne compileraient PAS. Il faudrait passer par des getters/setters (comme `setHitPoints(100)`), ce qui serait beaucoup plus lourd.

> **En résumé** : `protected` = "privé, mais mes enfants peuvent y toucher". `private` = "personne d'autre que moi ne peut y toucher, point."

---

## 2. 💎 Pourquoi `virtual` est crucial dans l'ex03 (le Diamond Problem)

L'ex03 crée un **DiamondTrap** qui hérite de **ScavTrap** ET **FragTrap**, qui eux-mêmes héritent tous les deux de **ClapTrap**. Voici la hiérarchie :

```
        ClapTrap
       /        \
  ScavTrap    FragTrap
       \        /
      DiamondTrap
```

### Sans `virtual` — LE PROBLÈME 💥

Sans `virtual`, `DiamondTrap` contiendrait **DEUX copies** de `ClapTrap` :
- Une qui vient de `ScavTrap`
- Une qui vient de `FragTrap`

Résultat :
- `this->_name` serait **ambigu** — lequel des deux `_name` ? Celui de `ScavTrap::ClapTrap` ou celui de `FragTrap::ClapTrap` ?
- Le compilateur donnerait une **erreur d'ambiguïté**
- Il y aurait **deux constructeurs** de `ClapTrap` appelés (donc deux messages "ClapTrap constructor called")

```
// SANS virtual : DiamondTrap contient :
[ClapTrap de ScavTrap] { _name, _hitPoints, _energyPoints, _attackDamage }
[ClapTrap de FragTrap] { _name, _hitPoints, _energyPoints, _attackDamage }
// → doublon ! ambiguïté ! 💥
```

### Avec `virtual` — LA SOLUTION ✅

```cpp
class ScavTrap : virtual public ClapTrap   // ← virtual
class FragTrap : virtual public ClapTrap   // ← virtual
```

Le mot-clé `virtual` dit au compilateur : **"Ne crée qu'UNE SEULE instance de `ClapTrap`"**, partagée entre `ScavTrap` et `FragTrap`.

```
// AVEC virtual : DiamondTrap contient :
[ClapTrap UNIQUE] { _name, _hitPoints, _energyPoints, _attackDamage }
// → pas d'ambiguïté ! ✅
```

C'est aussi pour ça que dans le constructeur de `DiamondTrap`, il faut **explicitement** appeler le constructeur de `ClapTrap` :
```cpp
DiamondTrap::DiamondTrap(std::string name)
    : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name)
```
Parce qu'avec l'héritage virtuel, c'est la **classe la plus dérivée** (`DiamondTrap`) qui est responsable d'initialiser la base virtuelle (`ClapTrap`), pas les classes intermédiaires.

---

## 3. 📛 Pourquoi 2 `_name` ?

`DiamondTrap.hpp` déclare son **propre** `_name` :
```cpp
class DiamondTrap : public ScavTrap, public FragTrap
{
    private:
        std::string _name;  // ← un _name PROPRE à DiamondTrap
};
```

Et `ClapTrap` a aussi un `_name` (hérité via `protected`).

**Pourquoi ?** Parce que le sujet demande que `DiamondTrap` ait son **propre nom** distinct du nom de `ClapTrap`. C'est visible dans `whoAmI()` :

```cpp
void DiamondTrap::whoAmI()
{
    std::cout << "DiamondTrap " << this->_name         // ← le nom DiamondTrap
              << " and ClapTrap " << ClapTrap::_name   // ← le nom ClapTrap
              << std::endl;
}
```

Concrètement, quand on fait `DiamondTrap d("Bobby")` :
- `DiamondTrap::_name` = `"Bobby"` (le nom du DiamondTrap)
- `ClapTrap::_name` = `"Bobby_clap_name"` (le nom du ClapTrap sous-jacent)

C'est le **but pédagogique** de l'exercice : montrer que dans un héritage en diamant, on peut avoir des attributs **du même nom** à des niveaux différents de la hiérarchie, et on utilise la résolution de portée (`ClapTrap::_name` vs `this->_name`) pour les distinguer. Quand on écrit `this->_name` dans `DiamondTrap`, C++ prend l'attribut **le plus proche**, c'est-à-dire celui de `DiamondTrap` lui-même (qui *masque/shadow* celui de `ClapTrap`).
