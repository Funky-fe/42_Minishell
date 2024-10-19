#include "minishell.h"

int	quote_handler(char c, int quotes)
{
	if (c == '\'')
	{
		if (quotes == 2)
			return (0);
		else if (!quotes)
			return (2);
	}
	else if (c == '\"')
	{
		if (quotes == 1)
			return (0);
		else if (!quotes)
			return (1);
	}
	return (quotes);
}

char	*quote_expander(char *cmd)
{
	int		i;
	int		qts;
	char	**result;

	i = -1;
	qts = 0;
	while (cmd[++i])
	{
		qts = quote_handler(cmd[i], qts);
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !qts)
			cmd[i] = SEP;
		else if ((cmd[i] == '\'' && qts == 2) || \
		(cmd[i] == '\"' && qts == 1))
			cmd[i] = SEP;
	}
	result = ft_split(cmd, SEP);
	if (!*result)
	{
		result = free_array(result);
		return (ft_strdup(""));
	}
	return (ft_array_copy(result));
}