# Liste des Tokens - Lexer

## Tokens Mandatory

- `WORD` → Mot (commande, argument, fichier)
- `PIPE` → `|` Pipe
- `REDIR_IN` → `<` Redirection entrée
- `REDIR_OUT` → `>` Redirection sortie (truncate)
- `REDIR_APPEND` → `>>` Redirection sortie (append)
- `REDIR_HEREDOC` → `<<` Here document
- `AND` → `&&` Opérateur logique AND
- `OR` → `||` Opérateur logique OR
- `SEMICOLON` → `;` Séparateur de commandes
- `AMPERSAND` → `&` Background
- `EOF` → Fin d'input

## Tokens Bonus

- `LPAREN` → `(` Subshell ouverture
- `RPAREN` → `)` Subshell fermeture
- `LBRACE` → `{` Groupe de commandes
- `RBRACE` → `}` Fin groupe
- `REDIR_FD_IN` → `<&` Aggregation FD
- `REDIR_FD_OUT` → `>&` Aggregation FD
- `DQUOTE` → `"` Double quote
- `SQUOTE` → `'` Simple quote
- `BACKSLASH` → `\` Inhibiteur
- `DOLLAR` → `$` Variable
- `TILDE` → `~` Tilde expansion