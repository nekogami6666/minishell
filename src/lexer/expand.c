#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

/* $VAR → getenv(VAR), $$ → PID, $? → last status */
static char	*var_value(const char *key, t_ms *ms)
{
	if (ft_strlen(key) == 1 && !ft_strncmp(key, "?", 1))
		return (ft_itoa(ms->last_status));
	if (ft_strlen(key) == 1 && !ft_strncmp(key, "$", 1))
		return (ft_itoa(getpid()));
	char *val = getenv(key);
	return (val ? ft_strdup(val) : ft_strdup(""));
}

char	*expand(char *word, t_ms *ms)
{
	char	*dst = ft_calloc(1, 1);
	size_t	i = 0;

	while (word[i])
	{
		if (word[i] == '$' && word[i + 1]
			&& (ft_isalnum(word[i + 1]) || word[i + 1] == '_'
				|| word[i + 1] == '?' || word[i + 1] == '$'))
		{
			size_t	j = i + 1;
			while (ft_isalnum(word[j]) || word[j] == '_')
				j++;
			char *key = ft_substr(word, i + 1, j - (i + 1));
			char *val = var_value(key, ms);
			char *tmp = ft_strjoin(dst, val);
			free(dst);
			dst = tmp;
			free(key);
			free(val);
			i = j;
		}
		else
		{
			char tmp[2] = {word[i], '\0'};
			char *tmp2 = ft_strjoin(dst, tmp);
			free(dst);
			dst = tmp2;
			i++;
		}
	}
	free(word);
	return (dst);
}
