#ifndef STRUCTS_H
# define STRUCTS_H

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
	t_token	*token;
	char	error;
	char	exit;
}	t_mini;

typedef struct s_expand
{
	char	**hold_str;
	int		ex;
	int		start;
	int		end;
	int		quotes;
	int		ex_n;
	int		i;
}	t_expand;

typedef struct s_executor
{
	t_token	*temp;
	char	**cmd;
	int		**fd;
	int		status;
	pid_t	*pid;
	int		n_pros;
}	t_executor;

#endif
