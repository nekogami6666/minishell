#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

t_token	*lex(char *line, t_ms *ms);
char	*expand(char *word, t_ms *ms);

#endif
