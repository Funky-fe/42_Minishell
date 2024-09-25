#include "minishell.h"

void	remove_var(char *var, char ***env)
{
	size_t	i;
	char	*temp_var;

	i = 0;
	if (!var || !env)
		return ;
	temp_var = ft_strjoin (var, "=");
	while (env[0][i] && ft_strncmp(env[0][i], temp_var, ft_strlen(temp_var)))
		i++;
	if (*env && env[0][i])
	{
		env[0][i] = free_ptr (env[0][i]);
		env[0][i] = env[0][i + 1];
		i++;
		while (env[0][i])
		{
			env[0][i] = env[0][i + 1];
			i++;
		}
		env[0][i] = NULL;
	}
	temp_var = free_ptr (temp_var);
}

void	bltin_unset(t_mini *ms, char **cmd, char ***env)
{
	while (*(++cmd))
		remove_var (*cmd, env);
	ms -> error = 0;
}
