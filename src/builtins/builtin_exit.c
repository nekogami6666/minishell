#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	ms_exit(char **argv, t_ms *ms)
{
	int	status = ms->last_status;

	if (argv[1])
		status = ft_atoi(argv[1]);
	printf("exit\n");
	ms->running = false;
	return (status);
}
