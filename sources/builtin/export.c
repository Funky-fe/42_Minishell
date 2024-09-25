#include "minishell.h"

int	get_var_pos(char *var, char **env)
{
	int		position;
	int		len;
	char	*var_temp;

	if (ft_strchr (var, '='))
	{
		
	}
	len = ft_strchr (var, '=') - var;
	if (!len)
		len = ft_strlen (var);
	var_temp = ft_calloc (len + 2, sizeof (char));
	position = 0;
	ft_strlcpy (var_temp, var, len + 2);
	var_temp[len] = '\0';
	while (env[position] && ft_strncmp (env[position], var_temp, len + 1))
		position++;
	var_temp = free_ptr (var_temp);
	return (position);
}

void	update_var(char *var, int var_pos, char ***env)
{
	char	**temp;

	if (!env[0][var_pos])
	{
		temp = ft_calloc (var_pos + 2, sizeof (char *));
		temp[var_pos] = ft_strdup (var);
		while (var_pos--)
			temp[var_pos] = ft_strdup (env[0][var_pos]);
		*env = free_array (*env);
		*env = temp;
	}
	else
	{
		env[0][var_pos] = free_ptr (env[0][var_pos]);
		env[0][var_pos] = ft_strdup (var);
	}
}

int	is_valid(char *var)
{
	int	i;
	int	ret;

	ret = 1;
	if (!var || (var && var[0] == '='))
		ret = 0;
	if (ft_isdigit (var[0]))
		ret = 0;
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			ret = 0;
		i++;
	}
	return (ret);
}

void	bltin_export(t_mini *ms, char **cmd, char ***env)
{
	int	i;
	int	var_pos;

	i = 1;
	if (!cmd[1])
		print_sorted_env(*env);
	while (cmd[i])
	{
		if (is_valid (cmd[i]))
		{
			var_pos = get_var_pos (cmd[i], *env);
			update_var (cmd[i], var_pos, env);
			ms -> error = 0;
		}
		else if (!is_valid (cmd[i]))
		{
			ft_putstr_fd("minishell : export: ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			ms -> error = 42;
		}
		else
			ms -> error = 0;
		i++;
	}
}
