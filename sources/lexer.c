#include "minishell.h"

// THIS WILL PUT A SEP BEFORE AND AFTER THE SIMBOLS >, < AND | LIKE: "string SEP|SEP string"
char	*ft_separator(char *cmd, int pos)
{
	int		i;
	int		k;
	char	*result;

	k = -1;
	i = -1;
	result = ft_calloc(ft_strlen(cmd) + 3, sizeof (char));
	if (!result)	
		return (NULL);
	while (++k < pos)
		result[k] = cmd[++i];
	i++;
	result[k++] = SEP;
	result[k++] = cmd[i++];
	if (cmd[i] != '|' && cmd[i] == cmd[i - 1])
		result[k++] = cmd[i++];
	result[k++] = SEP;
	while (cmd[i])
		result[k++] = cmd[i++];
	cmd = free_ptr(cmd);
	result[k] = '\0';
	return (result);
}

char	**ft_lexer(char *input)
{
	char	*cmd;
	char	**result;
	int		i;
	int		qts;

	cmd = ft_strdup(input);
	qts = 0;
	i = -1;
	while (cmd && cmd[++i])
	{
		if ((cmd[i] == '>' || cmd[i] == '<' || cmd[i] == '|' ) && !qts)
		{
			cmd = ft_separator(cmd, i);
			i += 2;
		}
		else if (cmd[i] == '\'' || cmd[i] == '\"')
			qts = quote_handler(cmd[i], qts);
	}
	if (qts)
		cmd = free_ptr(cmd);
	result = ft_split(cmd, SEP);
	cmd = free_ptr(cmd);
	return (result);
}
