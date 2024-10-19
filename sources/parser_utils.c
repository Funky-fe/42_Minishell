#include "minishell.h"

void	check_pipe(char *cmd, t_token **top)
{
	char	*input;

	input = NULL;
	if (!ft_strncmp(cmd, "|", 2))
	{
		input = readline("> ");
		if (input && !input[0])
		{
			input = free_ptr(input);
			return ;
		}
		ft_parser(top, input);
		input = free_ptr(input);
	}
}

char	**split_args(char *input)
{
	int		i;
	int		qts;
	char	*tmp;
	char	**ret;

	i = -1;
	qts = 0;
	tmp = NULL;
	while (input[++i])
	{
		if (input[i] == ' ' && !qts)
			input[i] = SEP;
		else if (input[i] == '\"' || input[i] == '\'')
			qts = quote_handler(input[i], qts);
	}
	ret = ft_split(input, SEP);
	tmp = free_ptr(tmp);
	return (ret);
}

int	builtin(char *token)
{
	char	**builtins;
	int		i;

	i = -1;
	builtins = ft_calloc(8, sizeof(char *));
	if (!builtins)
		return (-1);
	builtins[0] = ft_strdup("cd");
	builtins[1] = ft_strdup("echo");
	builtins[2] = ft_strdup("env");
	builtins[3] = ft_strdup("exit");
	builtins[4] = ft_strdup("export");
	builtins[5] = ft_strdup("pwd");
	builtins[6] = ft_strdup("unset");
	builtins[7] = NULL;
	while (builtins[++i])
	{
		if (!ft_strncmp(token, builtins[i], ft_strlen(token)))
		{
			builtins = free_array(builtins);
			return (1);
		}
	}
	builtins = free_array(builtins);
	return (0);
}