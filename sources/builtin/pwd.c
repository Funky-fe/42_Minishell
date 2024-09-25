#include "minishell.h"

void	bltin_pwd(t_mini *ms, char **cmd, char **env)
{
	size_t	i;

	if (cmd[1] && cmd[1][0] == '-')
	{
		ft_printf ("pwd: bad option -%c\n", cmd[1][1]);
		ms -> error = 1;
	}
	else if (cmd[1])
	{
		ft_printf ("pwd: to many arguments\n");
		ms -> error = 1;
	}
	else
	{
		i = 0;
		while (env && ft_strncmp (env[i], "PWD=", 4))
			i++;
		if (env && env[i])
			ft_printf ("%s\n", env[i] + 4);
	}
}
