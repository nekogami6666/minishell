#include <signal.h>
#include <readline/readline.h>
#include <stdio.h>
#include "minishell.h"

static void	sigint_hdl(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\nminishell$ ", 12);
}

void	set_signal_handlers(void)
{
	struct sigaction	act;

	act.sa_handler = sigint_hdl;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}
