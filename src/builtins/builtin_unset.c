#include <stdlib.h>
#include <stdio.h>

int	ms_unset(char **argv, char ***env)
{
	(void)env;
	for (int i = 1; argv[i]; i++)
	{
		if (unsetenv(argv[i]) == -1)
			perror("unset");
	}
	return (0);
}
