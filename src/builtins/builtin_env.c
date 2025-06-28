#include <stdio.h>

int	ms_env(char **env)
{
	for (size_t i = 0; env && env[i]; i++)
		printf("%s\n", env[i]);
	return (0);
}
