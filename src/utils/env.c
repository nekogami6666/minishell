#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

char	**dup_env(char **envp)
{
	size_t	i = 0;
	while (envp[i])
		i++;
	char	**cpy = ft_calloc(i + 1, sizeof(char *));
	for (size_t j = 0; j < i; j++)
		cpy[j] = ft_strdup(envp[j]);
	return (cpy);
}

void	cleanup_env(char **envp)
{
	for (size_t i = 0; envp && envp[i]; i++)
		free(envp[i]);
	free(envp);
}

/* --------------------------------------------------------------- */
/*  ft_free_split : ft_split で確保した NULL 終端配列を解放         */
/* --------------------------------------------------------------- */
void	ft_free_split(char **arr)
{
	size_t	i = 0;

	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
