#include "minishell.h"

int	after_valid(t_mini *ms, t_token *token, int tokentype)
{
	if (tokentype == PIPE && token->next && token->next->type == PIPE)
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n", \
		token->next->cmd);
		ms->error = 2;
		return (1);
	}
	else if ((tokentype == REDIRECT && token->next == NULL) || \
	(tokentype == REDIRECT && (token->next->type == PIPE || \
	token->next->type == REDIRECT || token->next->type == HEREDOC)))
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n", \
		token->cmd);
		ms->error = 2;
		return (1);
	}
	return (0);
}

int	ft_syntchecker(t_mini *ms)
{
	t_token	*token;

	token = ms->token;
	while (token)
	{
		if (token->type == REDIRECT)
		{
			if (after_valid(ms, token, REDIRECT))
				return (1);
		}
		else if (token->type == PIPE)
		{
			if (after_valid(ms, token, PIPE))
				return (1);
		}
		else if (ft_strchr(token->cmd, '\\'))
		{
			ft_printf("minishell: syntax error, token `\\' is not accepted\n");
			ms->error = 2;
			return (1);
		}
		token = token->next;
	}
	return (0);
}
