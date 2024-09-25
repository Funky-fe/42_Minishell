#include "minishell.h"

void	run_scmd(char **cmd, char **env)
{
	char	*path;
	char	*error;
	int		i;

	i = 3;
	while (!close(i))
		i++;
	path = find_path(cmd[0], env);
	if (!path)
	{
		error = ft_strjoin("minishell : ", cmd[0]);
		ft_putstr_fd(error, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		error = free_ptr (error);
		return ;
	}
	execve(path, cmd, env);
	path = free_ptr(path);
	error = ft_strjoin("minishell : ", cmd[0]);
	perror(error);
	error = free_ptr (error);
}

void	exit_child(t_mini *ms, char **cmd, int **fd, int code)
{
	int	i;

	ms -> error = code;
	ms -> input = free_ptr (ms -> input);
	ms -> token = free_token (ms -> token);
	ms -> env = free_array (ms -> env);
	cmd = free_array(cmd);
	i = -1;
	while (fd[++i])
		fd[i] = (int *) free_ptr((char *) fd[i]);
	fd = (int **) free_array((char **) fd);
	rl_clear_history ();
	unlink("__heredoc");
	i = 0;
	while (!close(i))
		i++;
	exit(ms -> error);
}

void	file_error_message(t_mini *ms, char *cmd)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(cmd, 2);
	ms -> error = 1;
}

void	handle_invalid_file(t_mini *ms)
{
	t_token	*temp;

	temp = ms->token;
	while (temp)
	{
		if (temp->type == HEREDOC)
			ms->error = 0;
		if (temp->type == ARG_FILE)
		{
			if (access(temp->cmd, F_OK))
			{
				file_error_message(ms, temp->cmd);
				ft_putstr_fd(": No such file or directory\n", 2);
			}
			else if (access(temp->cmd, R_OK) || access(temp->cmd, W_OK))
			{
				file_error_message(ms, temp->cmd);
				ft_putstr_fd(": Permission Denied\n", 2);
				ms -> error = 1;
			}
		}
		temp = temp->next;
	}
}

void	child(t_mini *ms, char **cmd, int **fd, int i)
{
	int	out;
	int	in;

	out = 0;
	in = 0;
	cmd = redirect(ms, cmd, &out, &in);
	if (!cmd || *cmd == NULL)
		handle_invalid_file(ms);
	if (i && !in)
		dup2(fd[i - 1][0], 0);
	if (fd[i] && !out)
		dup2(fd[i][1], 1);
	close_fds(fd);
	if (!check_bltn(ms, cmd, &ms->env))
	{
		run_scmd(cmd, ms -> env);
		exit_child(ms, cmd, fd, 127);
	}
	exit_child(ms, cmd, fd, ms -> error);
}
