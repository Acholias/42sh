# 📚 Module History

## Description
Ce module gère l’historique des commandes : navigation, recherche, sauvegarde persistante et restauration. Il permet à l’utilisateur de retrouver et de réutiliser ses commandes précédentes même si le shell a été fermé. Si l’exécutable est supprimé avec un « make fclean », le fichier de sauvegarde sera supprimé.

## Fichiers

### `history.c`
- Structure et gestion de la liste d'historique en mémoire
- Navigation dans l'historique (précédent/suivant)
- Ajout de nouvelles entrées
- Gestion de la position courante dans l'historique
- Sauvegarde temporaire de la ligne en cours lors de la navigation

### `persistence.c`
- Sauvegarde de l'historique sur disque (`~/.42sh_history`)
- Chargement de l'historique au démarrage
- Persistance entre les sessions du shell
- Gestion du fichier d'historique et des erreurs d'I/O

### `search.c`
- Recherche interactive dans l'historique (Ctrl+R)
- Filtrage des entrées par motif
- Navigation dans les résultats de recherche
- Affichage et sélection des correspondances

## Rôle dans le projet
Ce module offre la **mémoire** du shell. Il permet aux utilisateurs de retrouver rapidement leurs commandes passées, améliore la productivité et persiste les données entre les sessions.

**Caractéristiques** :
- Gestion complète du cycle de vie de l'historique
- Persistance sur disque
- Recherche et navigation efficaces

**Utilisé par** : Le module `terminal/readline.c` pour gérer les touches de navigation dans l'historique (↑/↓, PageUp/PageDown, Ctrl+R).