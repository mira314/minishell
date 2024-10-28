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

static int	is_delimiter(char *delimiter, char *str)
{
	size_t	i;
	size_t	len;

	if (delimiter == NULL && str == NULL)
		return (0);
	if (delimiter == NULL || str == NULL)
		return (1);
	len = ft_strlen(str) - 1;
	if ( len != ft_strlen(delimiter))
		return(1);
	i = 0;
	while (i < len)
	{
		if (delimiter[i] != str[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*handle_heredoc(char *delim)
{
	
	char	*result;
	char	*tmp;
	char	*result_tmp;

	result = NULL;
	result_tmp = NULL;
	while (1)
	{
		write(1, ">", 1);
		tmp = get_next_line(0);
		if (tmp == NULL)
		{
			ft_putstr_fd("\nThere is an error\n", 2);
			return (result);	
		}
		if (is_delimiter(delim, tmp) == 0)
		{
			free(tmp);
			return (result);
		}
		result_tmp = result;
		if (result_tmp == NULL)
			result = ft_strdup(tmp);
		else
			result = ft_strjoin(result_tmp, tmp);
		free(tmp);
		free(result_tmp);
		if (result == NULL)
			return (NULL);
	}
	return result;
}

static void redir_input(t_data *data)
{
	(void)data;
	/*******temporary data******/
	char	*file[]={"heredoc", "heredoc", "heredoc",NULL};
	/***************************/
	int		fd;
	int		i;
	char	*heredoc_result;
	int		fds[2];

	i = 0;
	while(file[i] != 0)
	{
		if (ft_strcmp(file[i], "heredoc") == 0)
		{
			heredoc_result = handle_heredoc("del");
			if (file[i + 1] == NULL)
			{
				pipe(fds);
				if (heredoc_result == NULL)
					write(fds[1], "", 1);
				else
					write(fds[1], heredoc_result, ft_strlen(heredoc_result));
				close(fds[1]);
				dup2(fds[0], 0);
				close (fds[0]);	
			}
			free(heredoc_result);
		}
		else if (file[i + 1] == NULL)
		{
			fd = open(file[i], O_RDONLY);
			dup2(fd, 0);
			close (fd);
		}
		i++;
	}
}

/*static void redir_output(t_data *data)
{
	(void)data;	
	
	char	*file[]={"out1", "out2", NULL};
	int		mode = 1;
	
	int	open_mode;
	int	fd;
	int	i;

	printf("D'ont worry, the output has just been redirected\n");
	i = 0;
	while(file[i] != 0)
	{
		open_mode = O_WRONLY | O_CREAT | O_TRUNC;
		if (mode == 1)
			open_mode = O_WRONLY | O_CREAT | O_APPEND;
		fd = open(file[i], open_mode, 0644);
		if (file[i + 1] != NULL)
			close(fd);
		else
		{
			dup2(fd, 1);
			close (fd);
		}
		i++;
	}
}*/

static void	handle_redir(t_data *data)
{
	redir_input(data);
	//redir_output(data);
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
	int		fd_in_backup;
	int		fd_out_backup;


	fd_out_backup = dup(1);
	fd_in_backup = dup(0);
	handle_redir(data);
	exec_one_cmd(data);
	dup2(fd_out_backup, 1);
	dup2(fd_in_backup, 0);
}