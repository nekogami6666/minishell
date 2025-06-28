#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>

typedef enum e_toktype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_APPEND
}	t_toktype;

typedef struct s_token
{
	t_toktype		type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef enum e_nodetype
{
	NODE_CMD,
	NODE_PIPE
}	t_nodetype;

typedef struct s_cmd
{
	char	**argv;
	int		in_fd;
	int		out_fd;
}	t_cmd;

typedef struct s_node
{
	t_nodetype			type;
	union
	{
		t_cmd			cmd;
		struct
		{
			struct s_node	*left;
			struct s_node	*right;
		}	pipe;
	};
}	t_node;

typedef struct s_ms
{
	char	**envp;
	int		last_status;
	bool	running;
}	t_ms;

/* utils */
char	**dup_env(char **envp);
void	cleanup_env(char **envp);
void    ft_free_split(char **arr);  
void	set_signal_handlers(void);
void	exit_perror(const char *msg);

/* lexer / parser / exec */
t_token	*lex(char *line, t_ms *ms);
void	free_tokens(t_token *toks);
t_node	*parse(t_token *tok, t_ms *ms);
void	free_ast(t_node *ast);
void	exec_ast(t_node *ast, t_ms *ms);

/* built-ins */
int		ms_echo(char **argv);
int		ms_cd(char **argv, char ***env);
int		ms_pwd(void);
int		ms_env(char **env);
int		ms_export(char **argv, char ***env);
int		ms_unset(char **argv, char ***env);
int		ms_exit(char **argv, t_ms *ms);

#endif
