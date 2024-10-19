#include "minishell.h"

char	*ft_array_copy(char **array)
{
	char	*new;
	char	*tmp;
	int		i;

	i = 0;
	new = ft_strdup(array[0]);
	while (array[++i])
	{
		tmp = new;
		new = ft_strjoin(tmp, array[i]);
		tmp = free_ptr(tmp);
	}
	array = free_array(array);
	return (new);
}

char	**ft_arraydup(char **array)
{
	char	**tmp;
	size_t	i;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i])
		i++;
	tmp = ft_calloc (i + 1, sizeof (char *));
	i = 0;
	if (!tmp)
		return (NULL);
	while (array[i])
	{
		tmp[i] = ft_strdup (array[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	ft_sa_handler(int sig, siginfo_t *sa, void *info)
{
	(void) info;
	ft_printf ("\n");
	if (sig == SIGINT && sa->si_pid)
	{
		rl_on_new_line ();
		rl_replace_line ("", 0);
		rl_redisplay ();
	}
}

void	ft_end(t_mini *ms, const char *message, const int exitnumber)
{
	int	i;

	if (message)
		ft_printf("%s", message);
	if (!exitnumber && !message)
		ft_printf("exit\n");
	ms->input = free_ptr(ms -> input);
	ms->token = free_token(ms -> token);
	ms->env = free_array(ms -> env);
	rl_clear_history();
	unlink("__heredoc");
	i = 0;
	while (!close(i))
		i++;
	exit(exitnumber);
}

char	**token_to_array(t_token *token)
{
	int		counter;
	int		k;
	char	**result;
	t_token	*tmp;

	tmp = token;
	counter = 0;
	k = -1;
	while (tmp && tmp->type != PIPE)
	{
		counter++;
		tmp = tmp->next;
	}
	result = ft_calloc((counter + 1), sizeof(char *));
	if (!result)
		return (NULL);
	while (++k < counter)
	{
		result[k] = ft_strdup(token->cmd);
		token = token->next;
	}
	result[k] = NULL;
	return (result);
}
