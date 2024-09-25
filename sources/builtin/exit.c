#include "minishell.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!(ft_isdigit (str[i]) || str[i] == '+'))
			return (0);
		i++;
	}
	return (1);
}

int	is_only_zeros(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] != '0')
			return (0);
	}
	return (1);
}

void	bltin_exit(t_mini *ms, char **cmd)
{
	int	code;

	if (!cmd[1])
	{
		cmd = free_array(cmd);
		ft_end (ms, NULL, 0);
	}
	if (is_only_zeros(cmd[1]) && !cmd[2])
	{
		cmd = free_array(cmd);
		ft_end (ms, NULL, 0);
	}
	if (is_valid_number (cmd[1]) && !cmd[2])
	{
		code = ft_atoi (cmd[1]);
		cmd = free_array(cmd);
		ft_end (ms, "exited with error number", code);
	}
	cmd = free_array(cmd);
	// MUDAR ISTO DPS LOL
	ft_end (ms, "- minishell : exit: to many arguments", 1);
}
