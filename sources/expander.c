#include "minishell.h"

char	*get_exitstatus(t_mini *ms, char *var, char *cmd)
{
	char	*ret;

	ret = NULL;
	if (!*cmd)
	{
		var = free_ptr(var);
		return (ft_strdup("$"));
	}
	if (cmd && cmd[0])
		ret = ft_strdup(++cmd);
	var = free_ptr(var);
	return (ft_strjoinn(ft_itoaa(ms->error), ret));
}

char	*get_env(t_mini *ms, char *cmd, char **env)
{
	char	*tmp;
	int		len;
	int		var_len;

	tmp = cmd;
	cmd++;
	if (*cmd == '{')
		len = ft_strlen(++cmd);
	else
		len = ft_strlen(cmd);
	if (*cmd == '?' || len == 0)
		return (get_exitstatus(ms, tmp, cmd));
	while (*env)
	{
		var_len = equalsign(*env);
		if (!ft_strncmp(cmd, *env, var_len))
		{
			tmp = free_ptr(tmp);
			return (ft_strdup(*env + len + 1));
		}
		env++;
	}
	tmp = free_ptr(tmp);
	return (ft_strdup(""));
}

/*
	Vamos contar quantas vezes vamos expandir para nao haver problemas 
	de memoria caso usamos aspas etc.
	No geral isto so vai fazer as verificacoes e expandir os $.
*/
char	*ft_expander(t_mini *ms, char *cmd, char **env)
{
	t_expander	ex;

	ft_bzero(&ex, sizeof(t_expander));
	while (cmd[ex.i]) 
	{
		if (cmd[ex.i++] == '$')
			ex.ex_n++;
	}
	ex.ex = (ex.ex_n * 2) + 2;
	ex.newcmd = ft_calloc(ex.ex, sizeof(char *));
	if (!ex.newcmd)
		return (NULL);
	ex.ex = 0;
	ex.end = -1;
	ex = init_ex(ms, cmd, env, ex);
	if (cmd[ex.start] == '$')
		ex.newcmd[ex.ex++] = get_env(ms, ft_substr(cmd, ex.start, \
		ex.end - ex.start), env);
	else
		ex.newcmd[ex.ex++] = ft_substr(cmd, ex.start, ex.end - ex.start);
	return (ft_array_copy(ex.newcmd));
}

void	ft_expand(t_mini *ms, t_token **top, char **env)
{
	t_token	*sub;
	char	*tmp;

	sub = *top;
	while (sub)
	{
		if (ft_strchr(sub->cmd, '$'))
		{
			tmp = sub->cmd;
			sub->cmd = ft_expander(ms, sub->cmd, env);
			if (sub->cmd == NULL)
				sub->cmd = tmp;
			else
				tmp = free_ptr(tmp);
		}
		if ((sub->prev && sub->prev->type != HEREDOC) || !sub->prev)
			sub->cmd = quote_expander(sub->cmd);
		sub = sub->next;
	}
}
