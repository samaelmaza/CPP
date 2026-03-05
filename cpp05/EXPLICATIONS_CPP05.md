# CPP05 — Résumé Détaillé pour la Défense

## Vue d'ensemble

Le CPP05 enseigne les **exceptions** en C++. Chaque exercice ajoute une couche :

| Exercice | Concept | Ce qui est ajouté |
|:---------|:--------|:------------------|
| ex00 | `throw` / `try` / `catch` | Bureaucrat avec exceptions |
| ex01 | Interaction entre classes via exceptions | Form + `beSigned()` / `signForm()` |
| ex02 | Classes abstraites + héritage | AForm + 3 formulaires concrets |
| ex03 | Pointeurs de fonctions | Intern + `makeForm()` |

---

## 🔑 Les Exceptions — Le concept central

### Pourquoi pas juste une fonction d'erreur ?

| Fonction d'erreur (`std::cout + return`) | Exception (`throw` / `catch`) |
|---|---|
| L'appelant peut **ignorer** l'erreur | L'appelant est **forcé** de gérer |
| Reste dans la même fonction | **Remonte automatiquement** la chaîne d'appels |
| Pas de type d'erreur | Chaque exception a **son propre type** |

### Les 3 mots-clés

```cpp
// THROW — lance une alarme (sort de la fonction immédiatement)
if (grade < 1)
    throw GradeTooHighException();  // tout le code après est ignoré

// TRY — "j'essaie un truc dangereux"
try {
    Bureaucrat b("Test", 0);     // ← ça va throw
    std::cout << "jamais affiché";  // ← cette ligne est sautée
}
// CATCH — "je rattrape l'alarme"
catch (std::exception &e) {      // ← on atterrit ici
    std::cout << e.what();       // ← affiche "Grade is too high!"
}
// le programme continue normalement ici
```

> `throw` = un `exit()` **récupérable**. Le programme ne meurt pas, il saute au `catch`.

---

## Ex00 — Bureaucrat

### La classe

```
Bureaucrat
├── const string _name
├── int _grade            (1 = le meilleur, 150 = le pire)
├── incrementGrade()      (3 → 2, vérifie avant de modifier)
├── decrementGrade()      (3 → 4, vérifie avant de modifier)
└── Exceptions imbriquées
    ├── GradeTooHighException
    └── GradeTooLowException
```

### Pourquoi les exceptions sont DANS la classe ?

Parce qu'elles sont **spécifiques à Bureaucrat**. On sait d'où vient l'erreur :
```cpp
catch (Bureaucrat::GradeTooHighException &e)  // → c'est le Bureaucrat qui a un problème
```

### La syntaxe de `what()`

```cpp
const char *what() const throw();
//   ↑        ↑      ↑      ↑
// retour   nom    ne      promet de ne
// string C       modif   lancer aucune
//                rien    exception
```

C'est la méthode héritée de `std::exception` qu'on redéfinit pour donner notre message.

---

## Ex01 — Form

### Le concept : 2 classes qui interagissent via exceptions

```
Bureaucrat ──signForm()──→ Form.beSigned()
                              ↓
                    grade suffisant ? → _isSigned = true ✅
                    grade trop bas ?  → throw GradeTooLowException ❌
```

### `beSigned()` (dans Form) — décide si le form accepte la signature

```cpp
void Form::beSigned(const Bureaucrat &b) {
    if (b.getGrade() > this->_gradeToSign)  // grade 100 > grade requis 50 → pas assez bon
        throw GradeTooLowException();
    this->_isSigned = true;
}
```

### `signForm()` (dans Bureaucrat) — essaie de signer et gère le résultat

```cpp
void Bureaucrat::signForm(Form &form) {
    try {
        form.beSigned(*this);                          // *this = "moi le bureaucrat"
        std::cout << _name << " signed " << form.getName();   // succès
    }
    catch (std::exception &e) {
        std::cout << _name << " couldn't sign " << form.getName()
                  << " because " << e.what();          // échec
    }
}
```

> C'est le premier vrai `try/catch` écrit **dans une classe**, pas juste dans le main.

---

## Ex02 — AForm (abstraite) + 3 formulaires concrets

### Le concept : comme CPP04 ex02

`Form` → `AForm` (on ajoute `= 0` pour rendre la classe abstraite).

### L'architecture élégante

```
AForm (abstraite)
├── execute()          → vérifie signé + grade (dans la BASE)
├── executeAction()    → = 0 (virtuelle pure, chaque enfant l'implémente)
│
├── ShrubberyCreationForm  (sign: 145, exec: 137) → crée un fichier avec des arbres
├── RobotomyRequestForm    (sign: 72, exec: 45)   → 50% succès robotomie
└── PresidentialPardonForm (sign: 25, exec: 5)     → pardon par Zaphod Beeblebrox
```

### Pourquoi `execute()` dans la base et `executeAction()` dans les enfants ?

```cpp
// DANS AForm (la base) — vérifie les permissions
void AForm::execute(Bureaucrat const &executor) const {
    if (_isSigned == false)
        throw FormNotSignedException();        // vérifié UNE SEULE fois ici
    if (executor.getGrade() > _gradeToExec)
        throw GradeTooLowException();           // vérifié UNE SEULE fois ici
    executeAction();                            // appelle la méthode de l'enfant
}
```

Si on vérifiait dans chaque enfant, on copierait le même code 3 fois. En le mettant dans la base, on le fait **une seule fois** → plus propre.

### `std::ofstream` (pour ShrubberyCreationForm)

```cpp
std::ofstream file((this->_target + "_shrubbery").c_str());
//             ↑          ↑                         ↑
//          variable    nom du fichier           .c_str() obligatoire en C++98
//          de type                             (ofstream veut un const char*, pas un string)
//          "fichier en écriture"
file << "texte" << std::endl;   // écrire dedans (comme cout mais dans un fichier)
file.close();
```

---

## Ex03 — Intern

### Le concept : pointeurs de fonctions

L'Intern crée des formulaires sans utiliser de if/else en chaîne.

### Comment ça marche

```cpp
AForm *Intern::makeForm(const std::string &name, const std::string &target)
{
    // Tableau de noms
    std::string names[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};

    // Tableau de pointeurs de fonctions — chaque case = une méthode create
    AForm *(Intern::*creators[3])(const std::string &) = {
        &Intern::createShrubbery,     // creators[0] → pointe vers createShrubbery
        &Intern::createRobotomy,      // creators[1] → pointe vers createRobotomy
        &Intern::createPresidential   // creators[2] → pointe vers createPresidential
    };

    for (int i = 0; i < 3; i++)
    {
        if (name == names[i])
            return (this->*creators[i])(target);
            //      ↑        ↑           ↑
            //   l'objet   la méthode   l'argument
    }
    return NULL;
}
```

### Pourquoi pas créer les 3 formulaires et choisir ensuite ?

Parce qu'on ne crée **QUE** le formulaire demandé. Si on crée les 3 et qu'on n'en retourne qu'un, les 2 autres sont des **fuites mémoire** (new sans delete).

---

## Questions pièges possibles

> **"C'est quoi la différence entre throw et exit ?"**
> `exit()` tue le programme. `throw` quitte la fonction mais peut être rattrapé par un `catch`. Le programme continue.

> **"Pourquoi virtual sur le destructeur de AForm ?"**
> Parce qu'on fait `delete` via des pointeurs `AForm*`. Sans virtual, seul `~AForm()` serait appelé, pas le destructeur de l'enfant.

> **"Pourquoi les exceptions héritent de std::exception ?"**
> Pour pouvoir toutes les attraper avec un seul `catch (std::exception &e)` grâce au polymorphisme.

> **"Pourquoi executeAction() est protected et pas public ?"**
> Parce que personne à l'extérieur ne doit l'appeler directement. On veut que tout passe par `execute()` qui vérifie les permissions d'abord.

> **"Pourquoi des pointeurs de fonctions dans l'Intern ?"**
> Le sujet interdit les longues chaînes de if/else. Et ça évite de créer les 3 formulaires à chaque appel (fuite mémoire).
