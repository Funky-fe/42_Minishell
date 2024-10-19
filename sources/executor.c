#include "minishell.h"

/*
	If the first process with a builtin command where it modifies something
	this will ensure that the changes are reflected in the parent process.
	aka, if no change, just make child (hehe)
*/
int	exec_on_parent(t_mini *ms, int processes, char **cmd, int **fd)
{
	if (processes > 1)
		return (-1);
	if (ft_strncmp (*cmd, "echo", 4) == 0)
		return (-1);
	if (ft_strncmp (*cmd, "env", 3) == 0)
		return (-1);
	if (ft_strncmp (*cmd, "pwd", 3) == 0)
		return (-1);
	if (ft_strncmp (*cmd, "exit", 5) == 0)
		fd = (int **) free_array((char **) fd);
	if (!check_bltn(ms, cmd, &ms->env))
		return (-1);
	return (processes);
}

void	exec_on_child(t_mini *ms, t_executor *exe, int i)
{
	exe->pid = malloc(sizeof(pid_t) * exe->processes);
	while (++i < exe->processes)
	{
		if (i)
			exe->cmd = token_to_array(exe->token);
		exe->pid[i] = fork();
		if (exe->pid[i] == 0)
			child(ms, exe->cmd, exe->fd, i);
		while (exe->token && exe->token->type != PIPE)
			exe->token = exe->token->next;
		if (exe->token && exe->token->type == PIPE)
			exe->token = exe->token->next;
		exe->cmd = free_array(exe->cmd);
	}
}

void	ft_executor(t_mini *ms)
{
	int			i;
	int			k;
	t_executor	exe;

	exe = init_exec(ms);
	i = exec_on_parent(ms, exe.processes, exe.cmd, exe.fd);
	if (i)
		exe.cmd = free_array(exe.cmd);
	exec_on_child(ms, &exe, i);
	close_fds(exe.fd);
	k = -1;
	while (exe.fd[++k])
		exe.fd[k] = (int *) free_ptr((char *) exe.fd[k]);
	exe.fd = (int **) free_array((char **) exe.fd);
	k = -1;
	while (++k < exe.processes)
		waitpid(exe.pid[k], &exe.status, 0);
	if (WIFEXITED(exe.status) && i != exe.processes)
		ms->error = WEXITSTATUS(exe.status);
	free(exe.pid);
}
