#include "minishell.h"

static char	*ft_getinput(t_mini *ms, const char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input && input[0])
		add_history(input);
	else if (!input)
		ft_end(ms, EXIT_MSG, 0);
	return (input);
}

void	ft_cleaner(t_mini *ms)
{
	ms->input = free_ptr(ms->input);
	ms->token = free_token(ms->token);
	unlink("__heredoc");
}

static void	ft_sa_handler(int sig, siginfo_t *info, void *context)
{
	(void) context;
	ft_printf ("\n");
	if (sig == SIGINT && info->si_pid)
	{
		rl_on_new_line ();
		rl_replace_line ("", 0);
		rl_redisplay ();
	}
}

static t_mini	ft_init(int argc, char **env)
{
	t_mini				ms;
	struct sigaction	sa;

	ft_bzero(&ms, sizeof(t_mini));
	if (argc != 1)
		ft_end(&ms, "To many arguments, correct usage: ./minishell", 1);
	ms.env = ft_arraydup(env);
	if (!ms.env)
		ft_end(&ms, "Can't allocate memory to environment variables", 1);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = ft_sa_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction (SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	return (ms);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	ms;

	(void)argv;
	ms = ft_init(argc, env);
	while (1)
	{
		ms.input = ft_getinput (&ms, "minishell > ");
		if (ms.input && *ms.input)
		{
			if (ft_parser (&ms.token, ms.input) == 0 && ft_syntchecker (&ms) == 0)
			{
				ft_expander (&ms, &ms.token, ms.env);
				ft_executor (&ms);
			}
		}
		ft_cleaner (&ms);
	}
	return (0);
}
