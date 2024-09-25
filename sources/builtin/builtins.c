#include "minishell.h"

int	check_bltn(t_mini *ms, char **cmd, char ***env)
{
	if (!cmd || !*env)
		return (0);
	if (ft_strncmp (*cmd, "echo", 5) == 0)
		bltin_echo (ms, cmd);
	else if (ft_strncmp (*cmd, "cd", 3) == 0)
		bltin_cd (ms, cmd, env);
	else if (ft_strncmp (*cmd, "pwd", 4) == 0)
		bltin_pwd (ms, cmd, *env);
	else if (ft_strncmp (*cmd, "export", 7) == 0)
		bltin_export (ms, cmd, env);
	else if (ft_strncmp (*cmd, "unset", 6) == 0)
		bltin_unset (ms, cmd, env);
	else if (ft_strncmp (*cmd, "env", 4) == 0)
		bltin_env (ms, cmd, env);
	else if (ft_strncmp (*cmd, "exit", 5) == 0)
		bltin_exit (ms, cmd);
	else
		return (0);
	return (1);
}
