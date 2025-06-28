#include "lexer.h"
#include "libft.h"
#include <ctype.h>
#include <stdlib.h>

static bool	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	add_tok(t_token **lst, t_toktype type, char *val)
{
	t_token *new = malloc(sizeof(*new));
	if (!new)
		exit_perror("malloc");
	new->type = type;
	new->value = val;
	new->next = NULL;
	while (*lst && (*lst)->next)
		lst = &(*lst)->next;
	if (*lst)
		(*lst)->next = new;
	else
		*lst = new;
}

static char	*read_word(const char *s, size_t *i, t_ms *ms)
{
	size_t	start = *i;
	bool	dq = false;
	bool	sq = false;

	while (s[*i])
	{
		if (!sq && s[*i] == '"' && (++(*i) || 1))
			dq = !dq;
		else if (!dq && s[*i] == '\'' && (++(*i) || 1))
			sq = !sq;
		else if (!dq && !sq && (isspace(s[*i]) || is_meta(s[*i])))
			break;
		else
			(*i)++;
	}
	return (expand(ft_substr(s, start, *i - start), ms));
}

t_token	*lex(char *line, t_ms *ms)
{
	t_token *lst = NULL;
	size_t	i = 0;

	while (line[i])
	{
		if (isspace(line[i]) && ++i)
			continue;
		if (line[i] == '|')
		{
			add_tok(&lst, TOK_PIPE, ft_strdup("|"));
			i++;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			add_tok(&lst, TOK_APPEND, ft_strdup(">>"));
			i += 2;
		}
		else if (line[i] == '>')
		{
			add_tok(&lst, TOK_REDIR_OUT, ft_strdup(">"));
			i++;
		}
		else if (line[i] == '<')
		{
			add_tok(&lst, TOK_REDIR_IN, ft_strdup("<"));
			i++;
		}
		else
			add_tok(&lst, TOK_WORD, read_word(line, &i, ms));
	}
	return (lst);
}

void	free_tokens(t_token *t)
{
	while (t)
	{
		t_token *n = t->next;
		free(t->value);
		free(t);
		t = n;
	}
}
