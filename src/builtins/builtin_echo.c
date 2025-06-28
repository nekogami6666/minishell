#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int	ms_echo(char **argv)
{
	int	i = 1;
	int	nl = 1;

	if (argv[1] && ft_strlen(argv[1]) == 2 && !ft_strncmp(argv[1], "-n", 2))
	{
		nl = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
