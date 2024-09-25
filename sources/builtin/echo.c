#include "minishell.h"

void	bltin_echo(t_mini *ms, char **cmd)
{
	int	nl;
	int	i;
	int	k;

	nl = 1;
	i = 1;
	while (cmd && cmd[i] && ft_strncmp (cmd[i], "-n", 2) == 0)
	{
		k = 2;
		while (cmd[i][k] == 'n')
			k++;
		if (cmd[i][k] != '\0')
			break ;
		nl = 0;
		i++;
	}
	while (cmd && cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[++i])
			ft_putchar_fd (' ', 1);
	}
	if (nl)
		ft_printf ("\n");
	ms -> error = 0;
}
