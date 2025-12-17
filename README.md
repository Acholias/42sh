# 42sh

Un shell POSIX complet avec gestion avancée de la ligne de commande, job control et outils de debug.

## 📁 Structure du Projet

### `src/` - Code source principal

#### **main.c**
Point d'entrée + boucle principale

#### **terminal/** - Gestion du terminal (mode raw)
- `init.c` - Initialisation/restauration terminal
- `keys.c` - Lecture et détection des touches
- `display.c` - Affichage et déplacement curseur

#### **line_editing/** - Édition de ligne interactive
- `buffer.c` - Buffer éditable (insertion/suppression)
- `cursor.c` - Gestion position curseur
- `readline.c` - Boucle de lecture principale
- `shortcuts.c` - Ctrl-A, Ctrl-E, Ctrl-K, etc.

#### **history/** - Historique des commandes
- `history.c` - Structure et navigation (↑↓)
- `persistence.c` - Save/load ~/.42sh_history
- `search.c` - Ctrl-R (recherche incrémentale)

#### **lexer/** - Tokenisation
- `tokenize.c` - Découpage en tokens
- `quotes.c` - Gestion quotes/inhibiteurs
- `operators.c` - Détection opérateurs (|, >, &&, etc.)

#### **parser/** - Analyse syntaxique
- `parser.c` - Construction AST
- `grammar.c` - Règles de grammaire
- `precedence.c` - Précédence des opérateurs
- `syntax_check.c` - Validation syntaxe

#### **expander/** - Expansions
- `variables.c` - ${VAR}, ${?}
- `tilde.c` - ~
- `globbing.c` - *, ?, []
- `command_sub.c` - $()
- `arithmetic.c` - $(())

#### **executor/** - Exécution
- `execute.c` - Point d'entrée exécution
- `simple_cmd.c` - fork + execve
- `pipeline.c` - Gestion pipes
- `redirections.c` - <, >, >>
- `logical_ops.c` - && et ||
- `subshell.c` - ()

#### **builtins/** - Built-ins
- `cd.c`, `echo.c`, `exit.c`
- `export.c`, `unset.c`, `set.c`
- `type.c`, `jobs.c`, `fg.c`, `bg.c`

#### **environment/** - Variables d'environnement
- `env.c` - Gestion env + variables locales
- `hash_table.c` - Table de hash pour variables
- `export.c` - Import/export

#### **jobs/** - Job control
- `job_list.c` - Liste des jobs
- `fg_bg.c` - Foreground/Background
- `process_groups.c` - setpgid, tcsetpgrp
- `job_status.c` - Tracking état des jobs

#### **signals/** - Gestion des signaux
- `handlers.c` - SIGINT, SIGTERM, SIGTSTP, etc.
- `setup.c` - Configuration signaux
- `child_signals.c` - Signaux dans processus enfants

#### **utils/** - Utilitaires généraux
- `strings.c`, `lists.c`, `arrays.c`
- `path.c` - Recherche dans PATH
- `errors.c`

### `debug_tools/` - Outils de debug
Compilés avec `-DDEBUG`
- `memory_tracker.c` - Tracking allocations/leaks
- `token_printer.c` - Affichage visuel tokens
- `ast_printer.c` - Affichage arbre AST
- `env_printer.c` - Dump environnement
- `history_printer.c` - Affichage historique
- `signal_tracer.c` - Log signaux
- `exec_tracer.c` - Trace exécution
- `debugger.c` - Mode debug interactif
- `colors.c` - Utilitaires couleurs/box drawing

### `include/` - Headers
- `shell.h` - Structures principales
- `lexer.h`, `parser.h`, `executor.h`
- `builtins.h`
- `debug.h` - Macros debug (DEBUG_MEMORY, etc.)

### `tests/` - Tests
- `unit/` - Tests unitaires par module
- `integration/` - Tests end-to-end
- `scripts/` - Scripts de test complexes

### Autres fichiers
- `libft/` - Ta libft
- `Makefile` - Règles: all, clean, fclean, re, debug, valgrind
- `.gitignore`
## 🔄 Pipeline d'Exécution

```
┌─────────────────┐
│  UTILISATEUR    │
│  tape ligne     │
└────────┬────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  TERMINAL I/O (raw mode)                │
│  - Lecture touches                      │
│  - Gestion curseur                      │
│  - Affichage                            │
└────────┬────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  LINE EDITING                           │
│  - Buffer éditable                      │
│  - Historique (↑↓)                      │
│  - Shortcuts (Ctrl-A, Ctrl-K, etc.)     │
└────────┬────────────────────────────────┘
         │
         │ [Utilisateur appuie sur Enter]
         │
         ▼
┌─────────────────────────────────────────┐
│  LEXER                                  │
│  Input:  "ls -la | grep test > out"     │
│  Output: [TOKEN_WORD:"ls"]              │
│          [TOKEN_WORD:"-la"]             │
│          [TOKEN_PIPE:"|"]               │
│          [TOKEN_WORD:"grep"]            │
│          [...]                          │
└────────┬────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  PARSER                                 │
│  Input:  tokens[]                       │
│  Output: AST (arbre syntaxique)         │
│          NODE_PIPE                      │
│          ├─ NODE_CMD: ls [-la]          │
│          └─ NODE_REDIR                  │
│             └─ NODE_CMD: grep [test]    │
└────────┬────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  EXPANDER                               │
│  - Remplace $VAR par valeurs            │
│  - Expand ~, *, ?, []                   │
│  - Command substitution $()             │
│  - Arithmetic $(())                     │
└────────┬────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  EXECUTOR                               │
│  - Fork processus                       │
│  - Setup pipes                          │
│  - Setup redirections                   │
│  - execve() ou built-in                 │
│  - Wait children                        │
└────────┬────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  CLEANUP                                │
│  - Free AST                             │
│  - Free tokens                          │
│  - Close FDs                            │
└─────────────────────────────────────────┘
```

## 🔨 Compilation

```bash
make          # Compilation standard
make debug    # Compilation avec symboles debug (-DDEBUG)
make valgrind # Vérification fuites mémoire
make clean    # Nettoyage objets
make fclean   # Nettoyage complet
make re       # Recompilation
```
