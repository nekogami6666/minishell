#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

bool	is_builtin(const char *cmd);
int		exec_builtin(t_cmd *c, t_ms *ms);
char	*search_path(const char *cmd, char **envp);

#endif
