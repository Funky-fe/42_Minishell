#include "minishell.h"

static char	*ft_getinput(t_mini *ms, const char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input && input[0])
		add_history(input);
	else if (!input)
		ft_end(ms, "exit\n", 0);
	return (input);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	ms;

	(void)argv;
	ms = ft_init_main(argc, env);
	while (1)
	{
		ms.input = ft_getinput (&ms, "minishell$ ");
		if (ms.input && *ms.input)
		{
			if (ft_parser (&ms.token, ms.input) == 0 && ft_syntchecker (&ms) == 0)
			{
				ft_expand (&ms, &ms.token, ms.env);
				ft_executor (&ms);
			}
		}
		ft_cleaner (&ms);
	}
	return (0);
}
