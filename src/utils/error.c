#include <stdio.h>
#include <stdlib.h>

void	exit_perror(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
