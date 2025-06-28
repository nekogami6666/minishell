#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>     /* ← 追加：open, O_CREAT など */

/* ------------------------------------------------------------------ */
/*  argv_from_tokens : WORD トークン列を argv[] に変換               */
/* ------------------------------------------------------------------ */
static char	**argv_from_tokens(t_token *first, t_token *last)
{
	size_t	count = 0;

	for (t_token *tmp = first; tmp && tmp != last; tmp = tmp->next)
		if (tmp->type == TOK_WORD)
			count++;
	char	**argv = ft_calloc(count + 1, sizeof(char *));
	size_t	i = 0;
	for (t_token *t = first; t && t != last; t = t->next)
		if (t->type == TOK_WORD)
			argv[i++] = ft_strdup(t->value);
	return (argv);
}

/* ------------------------------------------------------------------ */
/*  parse_argv : 連続する WORD を argv にする                         */
/* ------------------------------------------------------------------ */
char	**parse_argv(t_token **cur)
{
	t_token	*start = *cur;

	while (*cur && (*cur)->type == TOK_WORD)
		*cur = (*cur)->next;
	return (argv_from_tokens(start, *cur));
}

/* ------------------------------------------------------------------ */
/*  parse_redirs : <, >, >> を解析して fd をセット                    */
/* ------------------------------------------------------------------ */
void	parse_redirs(t_token **cur, t_cmd *cmd)
{
	while (*cur && (*cur)->type != TOK_PIPE)
	{
		if ((*cur)->type == TOK_REDIR_IN || (*cur)->type == TOK_REDIR_OUT
			|| (*cur)->type == TOK_APPEND)
		{
			int	op = (*cur)->type;

			*cur = (*cur)->next;
			if (!*cur || (*cur)->type != TOK_WORD)
				exit_perror("syntax");
			int	flags = (op == TOK_REDIR_OUT) ? O_CREAT | O_WRONLY | O_TRUNC
						: (op == TOK_APPEND)  ? O_CREAT | O_WRONLY | O_APPEND
						: O_RDONLY;
			int	fd = open((*cur)->value, flags, 0644);
			if (fd < 0)
				exit_perror("open");
			if (op == TOK_REDIR_IN)
				cmd->in_fd = fd;
			else
				cmd->out_fd = fd;
			*cur = (*cur)->next;
		}
		else
			break;
	}
}

/* ------------------------------------------------------------------ */
/*  parse_command / parse_pipeline / parse                           */
/* ------------------------------------------------------------------ */
static t_node	*parse_command(t_token **cur)
{
	t_cmd	cmd;

	cmd.argv = parse_argv(cur);
	cmd.in_fd = STDIN_FILENO;
	cmd.out_fd = STDOUT_FILENO;
	parse_redirs(cur, &cmd);
	t_node	*node = ft_calloc(1, sizeof(*node));
	node->type = NODE_CMD;
	node->cmd = cmd;
	return (node);
}

static t_node	*parse_pipeline(t_token **cur)
{
	t_node	*left = parse_command(cur);

	while (*cur && (*cur)->type == TOK_PIPE)
	{
		*cur = (*cur)->next;
		t_node	*right = parse_command(cur);
		t_node	*pipe_node = ft_calloc(1, sizeof(*pipe_node));
		pipe_node->type = NODE_PIPE;
		pipe_node->pipe.left = left;
		pipe_node->pipe.right = right;
		left = pipe_node;
	}
	return (left);
}

t_node	*parse(t_token *tok, t_ms *ms)
{
	(void)ms;
	return (parse_pipeline(&tok));
}

/* ------------------------------------------------------------------ */
/*  free_ast : 再帰的に AST ノードを解放                              */
/* ------------------------------------------------------------------ */
void	free_ast(t_node *n)
{
	if (!n)
		return ;
	if (n->type == NODE_CMD)
	{
		for (size_t i = 0; n->cmd.argv && n->cmd.argv[i]; i++)
			free(n->cmd.argv[i]);
		free(n->cmd.argv);
		if (n->cmd.in_fd != STDIN_FILENO)
			close(n->cmd.in_fd);
		if (n->cmd.out_fd != STDOUT_FILENO)
			close(n->cmd.out_fd);
	}
	else
	{
		free_ast(n->pipe.left);
		free_ast(n->pipe.right);
	}
	free(n);
}
