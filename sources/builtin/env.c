#include "minishell.h"

void	bltin_env(t_mini *ms, char **cmd, char ***env)
{
	size_t	i;

	if (cmd[1])
	{
		ft_putstr_fd ("minishell : env: invalid usage\n", 2);
		ms -> error = 42;
	}
	else
	{
		i = 0;
		while (env && *env && env[0][i])
		{
			if (ft_strchr(env[0][i], '='))
				ft_printf ("%s\n", env[0][i]);
			i++;
		}
		ms -> error = 0;
	}
}
