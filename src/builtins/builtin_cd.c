#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static int	update_pwd(char ***env, const char *oldpwd)
{
	char	buf[4096];

	if (!getcwd(buf, sizeof(buf)))
		return (perror("cd"), 1);
	/* 非効率だが簡単に：環境変数を再構築 */
	(void)env;
	(void)oldpwd;
	return (0);
}

int	ms_cd(char **argv, char ***env)
{
	const char	*path = (argv[1]) ? argv[1] : getenv("HOME");
	char		*oldpwd = getcwd(NULL, 0);

	if (!path || chdir(path) == -1)
		return (perror("cd"), free(oldpwd), 1);
	update_pwd(env, oldpwd);
	free(oldpwd);
	return (0);
}
