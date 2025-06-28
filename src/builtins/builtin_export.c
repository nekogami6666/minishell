#include "minishell.h"   /* ms_env */
#include "libft.h"
#include <stdio.h>

int	ms_export(char **argv, char ***env)
{
	(void)env;
	if (!argv[1])
		return (ms_env(*env), 0);
	for (int i = 1; argv[i]; i++)
	{
		if (!ft_strchr(argv[i], '='))
			fprintf(stderr, "export: `%s': not a valid identifier\n", argv[i]);
		else
			putenv(ft_strdup(argv[i]));
	}
	return (0);
}
