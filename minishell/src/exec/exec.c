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

static char	*get_doc(char *delim)
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
static int	handle_here_doc(int	*fds, char *del)
{
	char	*heredoc_result;
	int		exit_status;

	signal(SIGINT, SIG_IGN);
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fds[0]);
		heredoc_result = get_doc(del);
		if (heredoc_result == NULL)
			write(fds[1], "", 1);
		else
			write(fds[1], heredoc_result, ft_strlen(heredoc_result));
		close(fds[1]);
		free(heredoc_result);
		exit(0);
	}
	else
	{
		wait(&exit_status);
		if (WIFSIGNALED(exit_status))
		{
			signal(SIGINT, sig_int_handler);
			write(1,"\n", 1);
			return (-1);
		}	
	}
	signal(SIGINT, sig_int_handler);
	return (0);
}

static int redir_input(t_input *file)
{
	int		fd;
	int		i;
	int		fds[2];

	i = 0;
	while(file[i].filename != 0)
	{
		if (file[i].mode == HEREDOC)
		{
			pipe(fds);
			if (handle_here_doc(fds, file[i].filename) == -1)
			{
				close(fds[0]);
				close(fds[1]);
				return (-1);
			};
			close(fds[1]);
			if (file[i + 1].filename == NULL)
				dup2(fds[0], 0);
			close (fds[0]);	
		}
		else if (file[i + 1].filename == NULL)
		{
			fd = open(file[i].filename, O_RDONLY);
			dup2(fd, 0);
			close (fd);
		}
		i++;
	}
	return (0);
}

static void redir_output(t_output *file)
{
	int	open_mode;
	int	fd;
	int	i;

	i = 0;
	while(file[i].filename != 0)
	{
		open_mode = O_WRONLY | O_CREAT | O_TRUNC;
		if (file[i].mode == APPEND)
			open_mode = O_WRONLY | O_CREAT | O_APPEND;
		fd = open(file[i].filename, open_mode, 0644);
		if (file[i + 1].filename != NULL)
			close(fd);
		else
		{
			dup2(fd, 1);
			close (fd);
		}
		i++;
	}
}

static int	handle_redir(t_io_fd *io)
{
	if (redir_input(io->inputs))
		return (-1);
	redir_output(io->outputs);
	return (0);
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
	if (handle_redir(data->cmd->io) == -1)
		return ;
	exec_one_cmd(data);
	dup2(fd_out_backup, 1);
	dup2(fd_in_backup, 0);
}