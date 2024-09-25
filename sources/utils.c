#include "minishell.h"

void	ft_end(t_mini *ms, const char *message, const int exitnumber)
{
	int	i;

	if (exitnumber && exitnumber != 127)
		ft_putstr_fd (ERROR_MSG, 2);
	if (message)
		ft_putendl_fd ((char *) message, 2);
	if (!exitnumber && !message)
		ft_putendl_fd (EXIT_MSG, 1);
	ms->input = free_ptr (ms -> input);
	ms->token = free_token (ms -> token);
	ms->env = free_array (ms -> env);
	rl_clear_history ();
	unlink("__heredoc");
	i = 0;
	while (!close(i))
		i++;
	exit(exitnumber);
}

int	check_quotes(char c, int quotes)
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

char	*ft_array_copy(char **array)
{
	char	*str;
	char	*temp;
	int		i;

	str = ft_strdup(array[0]);
	i = 0;
	while (array[++i])
	{
		temp = str;
		str = ft_strjoin(temp, array[i]);
		temp = free_ptr(temp);
	}
	array = free_array(array);
	return (str);
}

char	**ft_arraydup(char **array)
{
	char	**temp;
	size_t	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		i++;
	temp = ft_calloc (i + 1, sizeof (char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (array[i])
	{
		temp[i] = ft_strdup (array[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
