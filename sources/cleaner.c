#include "minishell.h"

char	*free_ptr(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char	**free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array && array[i])
	{
		array[i] = free_ptr(array[i]);
		i++;
	}
	free (array);
	array = NULL;
	return (NULL);
}

t_token	*free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token -> cmd = free_ptr (token -> cmd);
		token = token -> next;
		free (tmp);
	}
	return (NULL);
}

void	ft_cleaner(t_mini *ms)
{
	ms->input = free_ptr(ms->input);
	ms->token = free_token(ms->token);
	unlink("__heredoc");
}

void	close_fds(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}