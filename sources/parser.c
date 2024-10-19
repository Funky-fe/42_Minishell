#include "minishell.h"

void	insert_token(t_token **top, char *cmd)
{
	t_token	*tmp;
	t_token	*token;

	token = init_token(cmd);
	token->cmd = ft_strdup(cmd);
	if (!*top)
	{
		*top = token;
		return ;
	}
	tmp = *top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
	token->prev = tmp;
}

void	insert_type(t_token **top)
{
	t_token	*token;

	token = *top;
	while (token)
	{
		if (!ft_strncmp(token->cmd, "|", ft_strlen(token->cmd)))
			token->type = PIPE;
		else if (!ft_strncmp(token->cmd, ">>", ft_strlen(token->cmd)) || \
		!ft_strncmp(token->cmd, "<", ft_strlen(token->cmd)))
			token->type = REDIRECT;
		else if (!ft_strncmp(token->cmd, "<<", ft_strlen("<<")))
			token->type = HEREDOC;
		else if (builtin(token->cmd))
			token->type = BUILTIN;
		else if (!token->prev || token->prev->type == PIPE)
			token->type = EXECVE;
		else if (token->prev->type == REDIRECT)
			token->type = ARG_FILE;
		else
			token->type = ARG;
		token = token->next;
	}
}

int	ft_parser(t_token **top, char *str)
{
	char	**cmdlist;
	char	**cmd;
	int		i;
	int		j;

	cmdlist = ft_lexer(str);
	if (!cmdlist)
	{
		ft_printf("minishell: parser: unclosed quotes\n");
		cmdlist = free_array(cmdlist);
		return (1);
	}
	i = -1;
	while (cmdlist[++i])
	{
		j = -1;
		cmd = split_args(cmdlist[i]);
		while (cmd[++j])
			insert_token(top, cmd[j]);
		cmd = free_array(cmd);
	}
	check_pipe (cmdlist[--i], top);
	cmdlist = free_array(cmdlist);
	insert_type(top);
	return (0);
}
