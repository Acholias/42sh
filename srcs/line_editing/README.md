# ✏️ Module Line Editing

## Description
Ce module fournit toutes les fonctions d'édition et de manipulation du buffer de ligne : insertion, suppression, déplacements du curseur, et raccourcis d'édition avancés.

## Fichiers

### `buffer.c`
- Insertion de caractères dans le buffer
- Suppression de caractères (delete, backspace)
- Gestion de la taille du buffer et des opérations sur les chaînes
- Validation et manipulation du contenu de la ligne

### `cursor.c`
- Déplacement du curseur dans le buffer
- Positionnement précis (début, fin, caractère spécifique)
- Gestion de la position logique dans la chaîne
- Validation des positions du curseur

### `mouvements.c`
- Déplacements par mot (Ctrl+Left_Arrow, Ctrl+Right_Arrow)
- Navigation avancée dans le buffer
- Détection des limites de mots et espaces
- Mouvements intelligents pour l'édition rapide

### `shortcuts.c`
- Raccourcis clavier (Ctrl+A, Ctrl+E, Ctrl+K, etc.)
- Opérations d'édition avancées (kill line, yank, transpose)
- Kill ring pour couper/coller
- Raccourcis de productivité pour l'utilisateur

## 🎹 Raccourcis clavier disponibles

### ✅ Navigation

- `←` / `Ctrl+B` → Déplacer le curseur d'un caractère vers la gauche
- `→` / `Ctrl+F` → Déplacer le curseur d'un caractère vers la droite
- `Ctrl+A` / `Home` → Aller au début de la ligne
- `Ctrl+E` / `End` → Aller à la fin de la ligne
- `Ctrl+←` / `Alt+B` → Reculer d'un mot
- `Ctrl+→` / `Alt+F` → Avancer d'un mot

### ✅ Édition basique

- `Backspace` → Supprimer le caractère avant le curseur
- `Delete` → Supprimer le caractère sous le curseur
- `Enter` → Valider et exécuter la commande

### ✅ Édition avancée

- `Ctrl+K` → Couper du curseur jusqu'à la fin de ligne (kill)
- `Ctrl+U` → Couper du début de ligne jusqu'au curseur
- `Ctrl+W` / `Alt+Backspace` → Supprimer le mot avant le curseur
- `Alt+D` → Supprimer le mot après le curseur
- `Ctrl+Y` → Coller le texte du kill ring (yank)
- `Ctrl+T` → Transposer (échanger) les deux caractères autour du curseur
- `Alt+T` → Transposer (échanger) les deux mots autour du curseur

### ✅ Transformation de texte

- `Alt+U` → Mettre le mot en MAJUSCULES
- `Alt+L` → Mettre le mot en minuscules
- `Alt+C` → Capitaliser le mot (première lettre en majuscule)

### ✅ Affichage

- `Ctrl+L` → Effacer l'écran et réafficher la ligne courante

### ✅ Historique

- `↑` → Commande précédente dans l'historique
- `↓` → Commande suivante dans l'historique
- `Page Up` → Remonter rapidement dans l'historique
- `Page Down` → Descendre rapidement dans l'historique
- `Ctrl+R` → Recherche interactive dans l'historique (reverse-i-search)
- `Ctrl+G` → Annuler la recherche interactive en cours

### ✅ Signaux

- `Ctrl+C` → Annuler la ligne courante (SIGINT)
- `Ctrl+D` → EOF - Quitter le shell si la ligne est vide
- `Ctrl+Z` → Suspendre le shell (SIGTSTP)

### ⏳ À implémenter

- `Alt+<` → Aller à la première entrée de l'historique
- `Alt+>` → Aller à la dernière entrée de l'historique
- `Ctrl+\` → Quitter avec core dump (SIGQUIT)
- `Tab` → Auto-complétion

## Rôle dans le projet
Ce module contient la **logique métier** de l'édition de ligne. Il fournit des fonctions utilitaires pures qui manipulent les structures de données sans se soucier de l'affichage ou du terminal.

**Caractéristiques** :
- Fonctions réutilisables et testables
- Indépendant du système d'affichage
- Pas de dépendances sur le terminal

**Utilisé par** : Le module `terminal` (notamment `readline.c`) pour traiter les actions utilisateur.