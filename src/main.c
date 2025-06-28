#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>  
#include <signal.h>

static t_ms	g_ms;

static void	init_minishell(char **envp)
{
	g_ms.envp = dup_env(envp);
	g_ms.last_status = 0;
	g_ms.running = true;
	set_signal_handlers();
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	init_minishell(envp);
	while (g_ms.running)
	{
		char	*line = readline("minishell$ ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		t_token	*toks = lex(line, &g_ms);
		t_node	*ast = parse(toks, &g_ms);
		exec_ast(ast, &g_ms);
		free(line);
		free_tokens(toks);
		free_ast(ast);
	}
	cleanup_env(g_ms.envp);
	return (g_ms.last_status);
}
