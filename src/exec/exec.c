#include "minishell.h"
#include "builtins.h"       /* exec_builtin, search_path */
#include "libft.h"
#include <stdio.h>          /* perror */
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/* ---- is_builtin -------------------------------------------------------- */
bool	is_builtin(const char *cmd)
{
	if (ft_strlen(cmd) == 4 && !ft_strncmp(cmd, "echo", 4))
		return (true);
	if (ft_strlen(cmd) == 2 && !ft_strncmp(cmd, "cd", 2))
		return (true);
	if (ft_strlen(cmd) == 3 && !ft_strncmp(cmd, "pwd", 3))
		return (true);
	if (ft_strlen(cmd) == 3 && !ft_strncmp(cmd, "env", 3))
		return (true);
	if (ft_strlen(cmd) == 6 && !ft_strncmp(cmd, "export", 6))
		return (true);
	if (ft_strlen(cmd) == 5 && !ft_strncmp(cmd, "unset", 5))
		return (true);
	if (ft_strlen(cmd) == 4 && !ft_strncmp(cmd, "exit", 4))
		return (true);
	return (false);
}

/* ---- child_exec -------------------------------------------------------- */
static void	child_exec(t_cmd *c, t_ms *ms)
{
	if (c->in_fd != STDIN_FILENO)
		dup2(c->in_fd, STDIN_FILENO);
	if (c->out_fd != STDOUT_FILENO)
		dup2(c->out_fd, STDOUT_FILENO);
	if (is_builtin(c->argv[0]))
		exit(exec_builtin(c, ms));
	char *path = search_path(c->argv[0], ms->envp);
	execve(path, c->argv, ms->envp);
	perror("execve");
	exit(127);
}

/* ---- pipe_launch ------------------------------------------------------- */
static void	pipe_launch(t_node *n, t_ms *ms, int in_fd)
{
	if (n->type == NODE_CMD)
	{
		pid_t pid = fork();
		if (pid == 0)
			child_exec(&n->cmd, ms);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		waitpid(pid, &ms->last_status, 0);
	}
	else
	{
		int	fd[2];

		pipe(fd);
		if (fork() == 0)
		{
			if (in_fd != STDIN_FILENO)
				dup2(in_fd, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			child_exec(&n->pipe.left->cmd, ms);
		}
		close(fd[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		pipe_launch(n->pipe.right, ms, fd[0]);
	}
}

/* ---- public ------------------------------------------------------------ */
void	exec_ast(t_node *ast, t_ms *ms)
{
	if (!ast)
		return ;
	if (ast->type == NODE_CMD && is_builtin(ast->cmd.argv[0]))
		ms->last_status = exec_builtin(&ast->cmd, ms);
	else
		pipe_launch(ast, ms, STDIN_FILENO);
	if (WIFEXITED(ms->last_status))
		ms->last_status = WEXITSTATUS(ms->last_status);
}
