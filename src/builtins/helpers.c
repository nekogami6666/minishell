#include "minishell.h"
#include "builtins.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

/* --------------------------------------------------------------- */
/*  search_path                                                     */
/* --------------------------------------------------------------- */
char	*search_path(const char *cmd, char **envp)
{
	(void)envp;                         /* ← unused-parameter 対策 */

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	char	*path = getenv("PATH");
	if (!path)
		return (ft_strdup(cmd));
	char	**dirs = ft_split(path, ':');
	for (size_t i = 0; dirs && dirs[i]; i++)
	{
		char *tmp  = ft_strjoin(dirs[i], "/");
		char *full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
		{
			ft_free_split(dirs);       /* ← ここで使用 */
			return (full);
		}
		free(full);
	}
	ft_free_split(dirs);
	return (ft_strdup(cmd));
}

/* --------------------------------------------------------------- */
/*  exec_builtin                                                    */
/* --------------------------------------------------------------- */
int	exec_builtin(t_cmd *c, t_ms *ms)
{
	if (!ft_strncmp(c->argv[0], "echo", 4) && ft_strlen(c->argv[0]) == 4)
		return (ms_echo(c->argv));
	if (!ft_strncmp(c->argv[0], "cd", 2) && ft_strlen(c->argv[0]) == 2)
		return (ms_cd(c->argv, &ms->envp));
	if (!ft_strncmp(c->argv[0], "pwd", 3) && ft_strlen(c->argv[0]) == 3)
		return (ms_pwd());
	if (!ft_strncmp(c->argv[0], "env", 3) && ft_strlen(c->argv[0]) == 3)
		return (ms_env(ms->envp));
	if (!ft_strncmp(c->argv[0], "export", 6) && ft_strlen(c->argv[0]) == 6)
		return (ms_export(c->argv, &ms->envp));
	if (!ft_strncmp(c->argv[0], "unset", 5) && ft_strlen(c->argv[0]) == 5)
		return (ms_unset(c->argv, &ms->envp));
	if (!ft_strncmp(c->argv[0], "exit", 4) && ft_strlen(c->argv[0]) == 4)
		return (ms_exit(c->argv, ms));
	return (1);
}
