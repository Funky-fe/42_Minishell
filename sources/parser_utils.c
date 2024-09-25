#include "minishell.h"

void	check_pipe(char *cmd, t_token **head)
{
	char	*input;

	input = NULL;
	if (!ft_strncmp(cmd, "|", 2))
	{
		input = readline("> ");
		if (input && !input[0])
		{
			input = free_ptr(input);
			return ;
		}
		ft_parser(head, input);
		input = free_ptr(input);
	}
}
