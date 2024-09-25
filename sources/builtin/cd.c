#include "minishell.h"

void	change_directory(t_mini *ms, char *dir, char ***env)
{
	char	**export;
	char	*currentdir;
	
	export = ft_calloc (3, sizeof (char *));
	export[0] = ft_strdup ("export");
	currentdir = getcwd (NULL, BUFFER_SIZE);
	if (!chdir (dir))
	{
		export[1] = ft_strjoin ("OLDPWD=", currentdir);
		bltin_export(ms, export, env);
		currentdir = free_ptr(currentdir);
		export[1] = free_ptr(export[1]);
		currentdir = getcwd(currentdir, BUFFER_SIZE);
		export[1] = ft_strjoin ("PWD=", currentdir);
		bltin_export(ms, export, env);
		ms->error = 0;
	}
	else
	{
		perror ("minishell : cd");
		ms->error = 42;
	}
	currentdir = free_ptr(currentdir);
	export = free_array(export);
}

char	*get_home(char **env)
{
	char	*home;

	while (env && ft_strncmp (*env, "HOME=", 5))
		env++;
	home = *env + 5;
	return (home);
}

void	bltin_cd(t_mini *ms, char **cmd, char ***env)
{
	if (cmd[1] && !cmd[2])
		change_directory(ms, cmd[1], env);
	else if (!cmd[1])
		change_directory(ms, get_home (*env), env);
	else
	{
		ft_putstr_fd("- minishell : cd: invalid usage\n", 2);
		ms->error = 42;
	}
}
