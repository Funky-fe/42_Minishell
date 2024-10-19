#ifndef STRUCTS_H
# define STRUCTS_H

#  ifndef SEP
#   define SEP -1
#  endif

enum e_type{
	PIPE = 10,
	EXECVE = 11,
	BUILTIN = 12,
	ARG = 13,
	ARG_FILE = 14,
	REDIRECT = 15,
	HEREDOC = 16
};

typedef struct s_token
{
	char			*cmd;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_mini
{
	char	*input;
	char	**env;
	char	error;
	char	exit;
	t_token	*token;
}	t_mini;

typedef struct s_expander
{
	char	**newcmd;
	int		ex;
	int		start;
	int		end;
	int		quotes;
	int		ex_n;
	int		i;
}	t_expander;

typedef struct s_executor
{
	t_token	*token;
	char	**cmd;
	int		**fd;
	int		status;
	pid_t	*pid;
	int		processes;
}	t_executor;

#endif
