#include "minishell.h"

t_mini	ft_init_main(int argc, char **env)
{
	t_mini				ms;
	struct sigaction	sa;

	if (argc != 1)
		ft_end(&ms, "To many arguments, correct usage: ./minishell", 1);
	ft_bzero(&ms, sizeof(t_mini));
	ms.env = ft_arraydup(env);
	if (!ms.env)
		ft_end(&ms, "Can't allocate memory for environment", 1);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = ft_sa_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction (SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	return (ms);
}

t_token	*init_token(char *cmd)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = 0;
	token->next = NULL;
	token->prev = NULL;
	token->cmd = ft_strdup(cmd);
	return (token);
}

/*
	Caso comece com $ vai logo expandir e guardar
	Caso não comece com $ vai entrar no primeiro if para ja guardar tudo
	ate chegar ao $.
	ex.newcmd vai ter tudo igual ao cmd normal mas vai expandir.
*/
t_expander	init_ex(t_mini *ms, char *cmd, char **env, t_expander ex)
{
	while (cmd[++ex.end])
	{
		ex.quotes = quote_handler(cmd[ex.end], ex.quotes);
		if (cmd[ex.end] == '$' && ex.quotes != 2)
		{
			ex.newcmd[ex.ex++] = ft_substr(cmd, ex.start, ex.end - \
			ex.start);
			ex.start = ex.end;
		}
		else if (cmd[ex.end] != '{' && cmd[ex.start] == '$' && \
		cmd[ex.end] != '?' && cmd[ex.end] != '_' \
		&& !ft_isalnum(cmd[ex.end]))
		{
			ex.newcmd[ex.ex++] = get_env(ms, ft_substr(cmd, ex.start, \
			ex.end - ex.start), env);
			if (cmd[ex.end] == '}' && cmd[ex.start + 1] == '{' \
			&& cmd[ex.end + 1])
				ex.end++;
			ex.start = ex.end;
		}
	}
	return (ex);
}

/*
	exe.processes que vai contar o numero de processos que vamos ter.
	exe.cmd vai ser o comando full ate o primeiro pipe aka primeiro processo.
*/
t_executor	init_exec(t_mini *ms)
{
	int			i;
	t_executor	exe;

	exe.token = ms->token;
	exe.cmd = token_to_array(exe.token);
	exe.status = 0;
	exe.pid = 0;
	exe.processes = 1;
	i = -1;
	while (exe.token)
	{
		if (exe.token->type == PIPE)
			exe.processes++;
		exe.token = exe.token->next;
	}
	exe.fd = ft_calloc(exe.processes, sizeof(int *));
	while (++i < (exe.processes - 1))
		exe.fd[i] = ft_calloc(2, sizeof(int));
	i = -1;
	while (++i < (exe.processes - 1))
		pipe(exe.fd[i]);
	exe.token = ms->token;
	return (exe);
}
