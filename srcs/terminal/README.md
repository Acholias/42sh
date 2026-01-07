# 🖥️ Module Terminal

## Description
Ce module gère toute l'interaction bas-niveau avec le terminal : configuration du mode raw, lecture des touches, affichage, gestion des signaux et la boucle principale de lecture interactive (readline).

## Fichiers

### `terminal_init.c`
- Initialisation du terminal en mode raw (permet de lire les entrées clavier caractère par caractère et de gérer manuellement les touches comme les	flèches, Ctrl+C ou Backspace)
- Sauvegarde et restauration de la configuration originale du terminal
- Active/désactive le mode de lecture caractère par caractère sans echo

### `keys.c`
- Lecture et décodage des séquences de touches du terminal
- Gestion des touches spéciales (flèches, home, end, delete, etc.)
- Traduction des séquences ANSI en codes de touches utilisables

### `display.c`
- Affichage du prompt et du buffer de ligne
- Rafraîchissement de l'affichage après modifications
- Gestion du curseur à l'écran (positionnement, déplacements)
- Effacement et mise à jour de la ligne affichée

### `signals.c`
- Gestion des signaux UNIX (SIGINT, SIGWINCH, SIGTSTP, SIGCONT)
- Handlers pour Ctrl+C, redimensionnement de la fenêtre, suspension
- Coordination entre les signaux et l'état de la ligne en cours

### `readline.c`
**Boucle principale d'édition de ligne interactive**
- Orchestre tous les modules (terminal, édition, historique, affichage)
- Gère le flux principal : lecture touche → traitement → affichage
- Coordonne la navigation dans l'historique
- Point d'entrée principal : `readline_loop()`

## Rôle dans le projet
Ce module est la **fondation** du système de ligne de commande interactive. Il expose l'interface système (terminal Unix) et fournit les primitives nécessaires aux autres modules pour construire une expérience d'édition de ligne complète.

**Dépendances** : Utilise les modules `line_editing` et `history` pour les opérations de haut niveau.