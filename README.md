# 42sh

Un shell POSIX complet avec gestion avancée de la ligne de commande, job control et outils de debug.

> **⚠️ PRINCIPE FONDAMENTAL : STABILITÉ > FEATURES**  
> Un 42sh simple mais indestructible vaut mieux qu'un 42sh avec plein de features qui segfault.  
> **Zéro** segfault, **zéro** memory leak, **zéro** comportement inattendu.

## 📁 Structure du Projet

### `src/` - Code source principal

#### **main.c**
Point d'entrée + boucle principale REPL (Read-Eval-Print Loop)

#### **terminal/** - Gestion du terminal (mode raw)
- `terminal_manager.c` - Regroupe les fonctions pour l'utilisation du terminal
- `term_init.c` - Initialisation/restauration terminal (termios)
- `keys.c` - Lecture et détection des touches
- `display.c` - Affichage et déplacement curseur
- `signals.c` - Gestion signaux en mode interactif (SIGINT, SIGTSTP)

#### **line_editing/** - Édition de ligne interactive
- `buffer.c` - Buffer éditable (insertion/suppression)
- `cursor.c` - Gestion position curseur
- `readline.c` - Boucle de lecture principale
- `shortcuts.c` - Ctrl-A, Ctrl-E, Ctrl-K, Ctrl-U, Ctrl-W, etc.
- `movement.c` - Flèches, Home, End, Ctrl-Left/Right

#### **history/** - Historique des commandes (BONUS)
- `history.c` - Structure et navigation (↑↓)
- `persistence.c` - Save/load ~/.42sh_history
- `search.c` - Ctrl-R (recherche incrémentale)

#### **lexer/** - Tokenisation
- `tokenize.c` - Découpage en tokens
- `quotes.c` - Gestion quotes/inhibiteurs (", ', \)
- `operators.c` - Détection opérateurs (|, >, &&, ||, ;, &, etc.)
- `heredoc.c` - Gestion <<

#### **parser/** - Analyse syntaxique
- `parser.c` - Construction AST
- `grammar.c` - Règles de grammaire POSIX
- `precedence.c` - **CRUCIAL** : Précédence des opérateurs (voir sujet)
- `syntax_check.c` - Validation syntaxe
- `error_recovery.c` - Messages d'erreur clairs

#### **expander/** - Expansions
- `variables.c` - ${VAR}, ${?}, $VAR
- `parameter.c` - ${parameter:-word}, ${parameter:=word}, etc. (BONUS)
- `tilde.c` - ~ expansion (BONUS)
- `globbing.c` - *, ?, [], ! (BONUS)
- `command_sub.c` - $() (BONUS)
- `arithmetic.c` - $(()) (BONUS)

#### **executor/** - Exécution
- `execute.c` - Point d'entrée exécution + dispatch
- `simple_cmd.c` - fork + execve basique
- `pipeline.c` - Gestion pipes (pipe(), dup2())
- `redirections.c` - <, >, >>, <<, >&, <&
- `logical_ops.c` - && et || (short-circuit evaluation)
- `sequence.c` - ; (séparateur)
- `background.c` - & (background execution)
- `subshell.c` - () (BONUS)

#### **builtins/** - Built-ins
**Mandatory:**
- `cd.c` - Change directory (gestion OLDPWD, CDPATH, etc.)
- `echo.c` - Echo avec options POSIX (-n)
- `exit.c` - Exit avec code retour
- `type.c` - Type de commande
- `export.c` - Export variables vers environnement
- `unset.c` - Suppression variables
- `set.c` - Liste variables internes
- `jobs.c` - Liste des jobs
- `fg.c` - Foreground
- `bg.c` - Background

**Bonus:**
- `alias.c`, `unalias.c`
- `hash.c`
- `test.c`
- `fc.c` (history)

#### **environment/** - Variables d'environnement
- `env.c` - Gestion env + variables locales (séparées!)
- `hash_table.c` - Table de hash pour variables internes
- `export.c` - Import/export entre local et env
- `special_vars.c` - $?, $0, $#, etc.

#### **jobs/** - Job control
- `job_list.c` - Liste des jobs (structure chainée)
- `fg_bg.c` - Foreground/Background switching
- `process_groups.c` - setpgid(), tcsetpgrp()
- `job_status.c` - Tracking état (running, stopped, done)
- `wait.c` - waitpid() avec WNOHANG, WUNTRACED

#### **signals/** - Gestion des signaux
- `handlers.c` - Handlers pour SIGINT, SIGTERM, SIGTSTP, SIGCHLD, etc.
- `setup.c` - Configuration signaux (sigaction)
- `child_signals.c` - Signaux dans processus enfants
- `interactive.c` - Comportement mode interactif vs script

#### **utils/** - Utilitaires généraux
- `strings.c` - ft_split, ft_strjoin, etc.
- `lists.c` - Listes chaînées
- `arrays.c` - Manipulation tableaux
- `path.c` - Recherche dans PATH
- `errors.c` - Messages d'erreur uniformes
- `memory.c` - Wrappers malloc/free avec tracking

### `debug_tools/` - Outils de debug
Compilés avec `-DDEBUG`
- `memory_tracker.c` - Tracking allocations/leaks
- `token_printer.c` - Affichage visuel tokens
- `ast_printer.c` - Affichage arbre AST (tree view)
- `env_printer.c` - Dump environnement
- `history_printer.c` - Affichage historique
- `signal_tracer.c` - Log signaux
- `exec_tracer.c` - Trace exécution (verbose mode)
- `debugger.c` - Mode debug interactif
- `colors.c` - Utilitaires couleurs/box drawing

### `include/` - Headers
- `shell.h` - Structures principales (t_shell, t_token, t_ast_node, etc.)
- `terminal.h` - Structures terminal (t_term, t_readline)
- `lexer.h`, `parser.h`, `executor.h`
- `builtins.h`
- `environment.h`
- `jobs.h`
- `debug.h` - Macros debug (DEBUG_MEMORY, DEBUG_TOKENS, etc.)

### `tests/` - Tests
- `unit/` - Tests unitaires par module (lexer, parser, etc.)
- `integration/` - Tests end-to-end (scripts complets)
- `edge_cases/` - Tests cas limites (quotes vides, pipes multiples, etc.)
- `comparison/` - Comparaison avec bash/sh
- `scripts/` - Scripts de test automatisés
- `memory/` - Tests valgrind

### Autres fichiers
- `libft/` - Ta libft
- `Makefile` - Règles: all, clean, fclean, re, debug, valgrind, test
- `.gitignore`
- `README.md` - Ce fichier
- `TESTING.md` - Guide de test
- `POSIX.md` - Notes sur conformité POSIX

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
│  - Lecture touches (read byte par byte) │
│  - Détection séquences escape (flèches) │
│  - Gestion curseur (ANSI codes)         │
│  - Affichage en temps réel              │
└────────┬────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  LINE EDITING                           │
│  - Buffer éditable (insertion anywhere) │
│  - Historique (↑↓)                      │
│  - Shortcuts (Ctrl-A, Ctrl-K, etc.)     │
│  - Multi-line si besoin                 │
└────────┬────────────────────────────────┘
         │
         │ [Utilisateur appuie sur Enter]
         │
         ▼
┌─────────────────────────────────────────┐
│  LEXER (Tokenisation)                   │
│  Input:  "ls -la | grep test > out"     │
│  Output: [TOKEN_WORD:"ls"]              │
│          [TOKEN_WORD:"-la"]             │
│          [TOKEN_PIPE:"|"]               │
│          [TOKEN_WORD:"grep"]            │
│          [TOKEN_WORD:"test"]            │
│          [TOKEN_REDIR_OUT:">"]          │
│          [TOKEN_WORD:"out"]             │
│                                         │
│  Gère: quotes, backslash, opérateurs    │
└────────┬────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  PARSER (Analyse syntaxique)            │
│  Input:  tokens[]                       │
│  Output: AST (arbre syntaxique)         │
│                                         │
│          NODE_PIPE                      │
│          ├─ NODE_CMD: ls [-la]          │
│          └─ NODE_REDIR (>)              │
│             ├─ file: "out"              │
│             └─ NODE_CMD: grep [test]    │
│                                         │
│  ⚠️ Respecte PRÉCÉDENCE des opérateurs  │
└────────┬────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  EXPANDER (Expansions)                  │
│  - Remplace $VAR, ${VAR}, ${?}          │
│  - Expand ~ (si bonus)                  │
│  - Globbing: *, ?, [] (si bonus)        │
│  - Command substitution $() (si bonus)  │
│  - Arithmetic $(()) (si bonus)          │
│                                         │
│  ⚠️ Ordre d'expansion important!        │
└────────┬────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  EXECUTOR (Exécution)                   │
│  1. Check si built-in → execute direct  │
│  2. Sinon:                              │
│     - Fork processus                    │
│     - Setup pipes (pipe + dup2)         │
│     - Setup redirections (open + dup2)  │
│     - Setup process groups (job ctrl)   │
│     - execve() dans enfant              │
│  3. Wait children (waitpid)             │
│  4. Update job status                   │
│  5. Store exit code in $?               │
└────────┬────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────┐
│  CLEANUP                                │
│  - Free AST (parcours post-order)       │
│  - Free tokens                          │
│  - Close FDs ouverts                    │
│  - Check memory leaks (si debug)        │
└─────────────────────────────────────────┘
```

## 🎯 Roadmap d'Implémentation

### Phase 0 : Setup ✅
- [x] Structure projet
- [x] Makefile
- [x] libft intégrée
- [x] Termios init

### Phase 1 : Readline Basique (1-2 semaines)
**Objectif** : Pouvoir taper une ligne et la récupérer
- [ ] Buffer simple (insertion, backspace)
- [ ] Affichage prompt
- [ ] Enter → retourne la ligne
- [ ] Ctrl+D (EOF)
- [ ] Ctrl+C (interrupt)
- [ ] Gestion basique curseur (←→)

**Test** : `42sh` affiche prompt, je tape "hello", ça affiche "hello"

### Phase 2 : Execution Minimale (1 semaine)
**Objectif** : Exécuter des commandes simples
- [ ] Lexer ultra-simple (split sur espaces)
- [ ] Parser minimal (une seule commande)
- [ ] Fork + execve
- [ ] PATH lookup
- [ ] Built-in exit
- [ ] Built-in echo (basique)
- [ ] $? (exit code)

**Test** : `ls`, `echo hello`, `/bin/ls`, `exit 42`

### Phase 3 : Variables (1 semaine)
**Objectif** : Gérer les variables shell
- [ ] Structure hash table variables
- [ ] Parsing `name=value`
- [ ] Expansion `$VAR` et `${VAR}`
- [ ] `${?}` pour exit code
- [ ] Built-in export
- [ ] Built-in unset
- [ ] Built-in set
- [ ] Distinction variables locales / environnement

**Test** : `VAR=hello`, `echo $VAR`, `export VAR`, `unset VAR`

### Phase 4 : Redirections (1-2 semaines)
**Objectif** : Gérer >, >>, <, <<, >&, <&
- [ ] Parsing redirections dans lexer
- [ ] AST avec nœuds redirection
- [ ] `>` (truncate)
- [ ] `>>` (append)
- [ ] `<` (input)
- [ ] `<<` (heredoc)
- [ ] `>&` et `<&` (aggregation)
- [ ] **ORDRE d'évaluation** (voir sujet!)

**Test** : `ls > out`, `cat < in`, `ls 2>&1`, heredoc

### Phase 5 : Pipes (1 semaine)
**Objectif** : Gérer les pipes
- [ ] Parsing `|`
- [ ] AST pipeline
- [ ] pipe() + fork multiples
- [ ] dup2() pour rediriger stdin/stdout
- [ ] Gestion erreurs (SIGPIPE)

**Test** : `ls | grep test`, `cat file | grep x | wc -l`

### Phase 6 : Opérateurs Logiques (1 semaine)
**Objectif** : &&, ||, ;
- [ ] Parsing &&, ||, ;
- [ ] AST avec nœuds logiques
- [ ] Short-circuit evaluation
- [ ] **PRÉCÉDENCE** (crucial!)
- [ ] Séquences de commandes

**Test** : `ls && echo ok`, `false || echo fail`, `ls ; pwd`

### Phase 7 : Job Control (2 semaines)
**Objectif** : Background, jobs, fg, bg
- [ ] Opérateur `&`
- [ ] Structure jobs list
- [ ] setpgid() / tcsetpgrp()
- [ ] Built-in jobs
- [ ] Built-in fg
- [ ] Built-in bg
- [ ] Gestion SIGCHLD
- [ ] Gestion SIGTSTP (Ctrl+Z)

**Test** : `sleep 10 &`, `jobs`, `fg`, `bg`

### Phase 8 : Signaux Complets (1 semaine)
**Objectif** : Tous les signaux corrects
- [ ] SIGINT (Ctrl+C) en mode interactif
- [ ] SIGQUIT (Ctrl+\)
- [ ] SIGTSTP (Ctrl+Z)
- [ ] SIGCHLD (reaping zombies)
- [ ] SIGTERM
- [ ] Propagation correcte aux enfants
- [ ] Masquage signaux au bon moment

**Test** : Ctrl+C n'arrête pas le shell, kill processes correctement

### Phase 9 : Built-ins Avancés (1 semaine)
**Objectif** : Finir tous les built-ins mandatory
- [ ] cd complet (-, OLDPWD, CDPATH)
- [ ] type complet
- [ ] echo avec toutes options POSIX
- [ ] Tous les built-ins conformes POSIX

**Test** : `cd -`, `cd ~`, `type ls`, `type cd`

### Phase 10 : Polish & Stabilisation (2 semaines minimum)
**Objectif** : ZÉRO bug
- [ ] Tests exhaustifs (tous les edge cases)
- [ ] Valgrind sur TOUT
- [ ] Gestion d'erreurs partout
- [ ] Messages d'erreur clairs
- [ ] Cas limites (pipes multiples, redirections complexes)
- [ ] Comparaison avec bash/sh
- [ ] Code review complet
- [ ] Norminette

**Test** : Lancer les 100+ tests, tout doit passer

### Phase 11+ : Bonus (si temps et si stable)
Ordre suggéré :
1. Quotes/inhibiteurs (", ', \)
2. Globbing (*, ?, [])
3. Historique (↑↓, Ctrl+R)
4. Autres expansions
5. Etc.

## 🔨 Compilation

```bash
make          # Compilation standard
make debug    # Compilation avec -DDEBUG -g3 -fsanitize=address
make valgrind # Lance valgrind --leak-check=full
make test     # Lance suite de tests
make clean    # Nettoyage objets
make fclean   # Nettoyage complet
make re       # Recompilation
```

## 🧪 Tests Critiques

### Tests Minimum (à passer AVANT correction)
```bash
# Commandes simples
ls
ls -la
/bin/ls
echo hello world
exit
exit 42

# Variables
VAR=hello
echo $VAR
export VAR
env | grep VAR
unset VAR

# Redirections
echo hello > out
cat < out
echo hello >> out
cat << EOF
ls 2>&1
ls 2>&1 > out  # Ordre important!
ls > out 2>&1  # Ordre différent!

# Pipes
ls | cat
ls | grep test
ls | grep test | wc -l

# Opérateurs logiques
true && echo ok
false || echo fail
ls ; pwd
false && echo should not print

# Job control
sleep 10 &
jobs
fg
# Ctrl+Z
bg

# Signaux
# Ctrl+C ne doit PAS quitter le shell
# Ctrl+D sur ligne vide doit quitter
# Ctrl+Z doit stopper foreground job

# Built-ins
cd /tmp
pwd
cd -
type ls
type cd
set
export TEST=value
unset TEST

# Edge cases
echo ""
echo ''
ls | | cat  # syntax error
> out       # syntax error
cat < < in  # syntax error
```

## ⚠️ Pièges Courants

### 1. Précédence des opérateurs
```bash
# Ces deux commandes sont DIFFÉRENTES:
ls doesnotexist . 2>&1 >/dev/null
ls doesnotexist . >/dev/null 2>&1
```

### 2. Memory leaks
- Toujours free l'AST
- Toujours free les tokens
- Close TOUS les FDs ouverts
- Attention aux leaks dans les signaux

### 3. File Descriptors
- Ne jamais oublier de close() après fork
- dup2() puis close() l'ancien FD
- Attention aux FDs hérités

### 4. Signaux
- sigaction, PAS signal()
- SA_RESTART pour certains signaux
- Masquer signaux pendant sections critiques

### 5. Job Control
- setpgid() AVANT execve()
- tcsetpgrp() pour donner contrôle terminal
- Reaper les zombies (SIGCHLD)

### 6. Quotes
- `"$VAR"` → expand
- `'$VAR'` → literal
- `\$VAR` → literal

## 📚 Ressources

- **POSIX Shell Spec** : https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
- **Termios** : `man termios`, `man tcgetattr`
- **Signals** : `man sigaction`, `man signal`
- **Job Control** : `man setpgid`, `man tcsetpgrp`
- **Testing** : Compare avec bash/sh
