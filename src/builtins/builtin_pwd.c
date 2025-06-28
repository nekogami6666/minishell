#include <unistd.h>
#include <stdio.h>

int	ms_pwd(void)
{
	char	buf[4096];

	if (getcwd(buf, sizeof(buf)))
	{
		printf("%s\n", buf);
		return (0);
	}
	perror("pwd");
	return (1);
}
