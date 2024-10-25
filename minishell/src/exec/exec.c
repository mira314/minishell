#include "exec.h"

static int	is_path(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (0);
		i++;
	}
	return (-1);
}

static int	exec_with_fork(char *path, char **args, char **envs)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		perror("Forking");
		return (1);
	}
	if (pid == 0)
	{
		if(execve(path, args, envs) == -1)
		perror(path);
		exit(127);
	}else
	{
		wait(&status);
	}
	return (WEXITSTATUS(status));
}

static void redir_input(t_data *data)
{
	(void)data;
	printf("I am handling the input redirection\n");
}

static void redir_output(t_data *data)
{
	(void)data;	
	char	*file[]={"out1", "out2", NULL};
	int	fd;
	int	i;

	printf("D'ont worry, the output has just been redirected\n");
	i = 0;
	while(file[i] != 0)
	{
		if (file[i + 1] != NULL)
		{
			fd = open(file[i], O_WRONLY | O_CREAT, 0644);
			close(fd);
		}
		else
		{
			fd = open(file[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, 1);
			close (fd);
		}
		i++;
	}
}

static void	handle_redir(t_data *data)
{
	redir_input(data);
	redir_output(data);
}

void	exec_one_cmd(t_data	*data)
{
	char	*path;
	char	*total_path;

	if (handles_bultin(data) == SUCCESS)
		return ;
	path = is_in_path_env(data->cmd->cmd, data->env);
	if (path != NULL)
	{
		total_path = build_path(path, data->cmd->cmd);
		free(path);
		if (total_path == NULL)
		{
			g_last_val = 1;
			return ;
		}
		g_last_val = exec_with_fork(total_path, data->cmd->args, data->env); 
		free(total_path);
		return ;
	}
	else if (is_path(data->cmd->cmd) == 0)
		g_last_val = exec_with_fork(data->cmd->cmd, data->cmd->args, data->env);
	else
		print_error(data->cmd->cmd, ": command not found\n", 127);
}

void	exec_with_redir(t_data *data)
{
	//int		fd_in_backup;
	int		fd_out_backup;

	fd_out_backup = dup(1);
	handle_redir(data);
	exec_one_cmd(data);
	dup2(fd_out_backup, 1);
}