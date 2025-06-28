#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

t_node	*parse(t_token *tok, t_ms *ms);

/* helpers exposed to exec/redir */
char	**parse_argv(t_token **cur);
void	parse_redirs(t_token **cur, t_cmd *cmd);

#endif
