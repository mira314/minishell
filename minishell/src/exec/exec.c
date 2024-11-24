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
	int	exit_status;

	pid = fork();
	if (pid == -1)
	{
		perror("Forking");
		return (1);
	}
	if (pid == 0)
	{
		errno = 0;
		signal(SIGINT, SIG_DFL);
		if(execve(path, args, envs) == -1)
		perror(path);
		if (errno == EACCES)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		else 
			exit(126);
	}else
	{
		wait(&status);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = 130;
	}
	return (exit_status);
}

int	is_delimiter(char *delimiter, char *str)
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
int	handle_here_doc(int	*fds, char *del, t_term *term)
{
	char	*heredoc_result;
	int		exit_status;

	signal(SIGINT, SIG_IGN);
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fds[0]);
		dup2(term->keybord_backup, 0);
		dup2(term->term_backup, 1);
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

static int redir_input(t_input *file, t_term *term)
{
	int		input;
	int		i;
	(void)term;

	i = 0;
	while(file[i].filename != 0)
	{
		input = open(file[i].filename, O_RDONLY);
		if (input == -1)
		{
			perror(file[i].filename);
			return (-1);
		}
		if (file[i + 1].filename == NULL)
				dup2(input, 0);
			close (input);
		i++;
	}
	return (0);
}

static int redir_output(t_output *file)
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
		if (fd == -1)
		{
			perror(file[i].filename);
			return (-1);
		}
		if (file[i + 1].filename != NULL)
			close(fd);
		else
		{
			if (dup2(fd, 1) == -1)
			{
				perror(file[i].filename);
				return (-1);
			}
			close (fd);
		}
		i++;
	}
	return (0);
}

static int	handle_redir(t_io_fd *io, t_data *data)
{
	if (redir_input(io->inputs, &data->term_backup) == -1)
		return (-1);
	if (redir_output(io->outputs) == -1)
		return (-1);
	return (0);
}

static void close_pipe(int *fds)
{
    close(fds[0]);
    close(fds[1]);
}

int  on_forking_error_pipe(int *fds)
{
    perror("Forking");
    close_pipe(fds);
    return (1);
}   

int fork_fun(int *input, int *output, t_data *data, t_cmd *cmd)
{
	int result;

    if (input != NULL)
    {
        close(input[1]);
        dup2(input[0], 0);
        close(input[0]);
    }
	if (output != NULL)
	{
		close(output[0]);
		dup2(output[1], 1);
		close(output[1]);
	}
    result = exec_with_redir(data, cmd);
	return (result);
}

// int    pipe_loop(t_data *data, t_cmd *cmd, int *pipe_in)
// {
//     int     pipe_out[2];
//     //int     pid;
//     int     status;
// 	//int		result;

// 	if (cmd->next == NULL)
// 	{
// 		if (fork() == 0)
// 		{
// 			status = fork_fun(pipe_in, pipe_out, data, cmd);
// 			exit (status);
// 		}
// 		else
// 		{
// 			if (pipe_in != NULL)
// 				close_pipe(pipe_in);
// 			wait(&status);
// 			return (WEXITSTATUS(status));
// 		}
// 	}
// 	else
// 	{
// 		if (pipe(pipe_out) == -1)
//     	{
//         	perror("piping");
//         	return (1);
//    		}
// 		if (fork() == 0)
// 		{
// 			status = fork_fun(pipe_in, pipe_out, data, cmd);
// 			exit (status);
// 		}
// 		else
// 		{
// 			if (pipe_in != NULL)
// 				close_pipe(pipe_in);
// 			wait(NULL);
// 			return (pipe_loop(data, cmd->next, pipe_out));
// 		}
		
// 	}
// }

int	count_cmd (t_cmd *cmd)
{
	int result;

	result = 0;
	while (cmd)
	{
		result++;
		cmd = cmd->next;
	}
	return (result);
}

void clean_pipes(int **pipes, int size)
{
	int	i;

	if (pipes == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	**create_pipes(int pipe_count)
{
	int	**result;
	int	i;

	result = (int **)malloc(sizeof(int *) * pipe_count);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		result[i] = (int *)malloc(sizeof(int) * 2);
		if (result[i] == NULL)
		{
			clean_pipes(result, i);
			return (NULL);
		}
		i++;
	}
	return (result);
}
void close_one_pipe_fd(int *fds)
{
	if (fds == NULL)
		return ;
	close(fds[0]);
	close(fds[1]);
}

void close_all_pipes(int **pipe_fds, int size)
{
	int i;
	
	if (pipe_fds == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		close_one_pipe_fd(pipe_fds[i]);
		i++;
	}
}
int	init_pipes(int **pipe_fds, int size)
{
	int i;

	if (pipe_fds == NULL)
		return (-1);
	i = 0;
	while (i < size)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			close_all_pipes(pipe_fds, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

void close_unused_pipe(int **pipe_fds, int size, int current_index)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i != current_index && i != current_index - 1)
			close_one_pipe_fd(pipe_fds[i]);
		i++;
	}
}

void fork_and_execute(t_data *data, int **pipe_fds, t_cmd *current_cmd, int cmd_count, int i)
{
	int pid;
	int exit_code;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close_unused_pipe(pipe_fds, cmd_count - 1, i);
		if (i == 0)
			exit_code = (fork_fun(NULL, pipe_fds[i],data, current_cmd));
		else if (i == cmd_count -1)
			exit_code = (fork_fun(pipe_fds[i - 1], NULL, data, current_cmd));
		else
			exit_code = (fork_fun(pipe_fds[i - 1], pipe_fds[i], data, current_cmd));
		clean_pipes(pipe_fds, cmd_count - 1);
		free_and_exit(data, exit_code);
	}
}

int	pipe_loop(t_data *data)
{
	int cmd_count;
	int	**pipe_fds;
	int	i;
	int	status;
	t_cmd *current_cmd;

	current_cmd = data->cmd;
	cmd_count = count_cmd(current_cmd);
	pipe_fds = create_pipes(cmd_count - 1);
	if (init_pipes(pipe_fds, cmd_count - 1) == -1)
		return (1);
	i = 0;
	while(i < cmd_count)
	{
		fork_and_execute(data, pipe_fds, current_cmd, cmd_count, i);
		current_cmd = current_cmd->next;
		i++;
	}
	close_all_pipes(pipe_fds, cmd_count - 1);
	i = -1;
	while (++i < cmd_count)
		wait (&status);
	clean_pipes(pipe_fds, cmd_count - 1);
	return (WEXITSTATUS(status));
}


void	exec(t_data *data)
{
	t_cmd *cmd;

	cmd = data->cmd;
	if (cmd->next == NULL)
		data->exit_value = exec_with_redir(data, cmd);
	else
		data->exit_value = pipe_loop(data);
}

static int execute_path(t_data *data, t_cmd *cmd, char *path)
{
	int 		result;
	struct stat path_stat;
	
	if (stat(path, &path_stat) == -1)
		return (1);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (126);
	}
	result = exec_with_fork(path, cmd->args + cmd->offset, data->env);
	return (result);
}

int	exec_one_cmd(t_data	*data,  t_cmd *cmd)
{
	char	*path;
	char	*total_path;
	int 	exit_status;

	if (cmd->cmd == NULL)
		return (0);
	if (handle_var(cmd->args, &data->var, &cmd->offset) == SUCCESS)
		return (0);
	if (handles_bultin(data, cmd) == SUCCESS)
		return (data->exit_value);
	path = is_in_path_env(cmd->args[cmd->offset], data->env);
	if (path != NULL)
	{
		total_path = build_path(path, cmd->args[cmd->offset]);
		free(path);
		if (total_path == NULL)
			return (1);
		exit_status = exec_with_fork(total_path, cmd->args + cmd->offset, data->env); 
		free(total_path);
		return (exit_status);
	}
	else if (is_path(cmd->args[cmd->offset]) == 0)
		exit_status = execute_path(data, cmd, cmd->args[cmd->offset]);
	else
	{
		exit_status = 127;
		print_error(cmd->args[cmd->offset], ": command not found\n", 127);
	}
	return (exit_status);
}

int	exec_with_redir(t_data *data, t_cmd *cmd)
{
	int		fd_in_backup;
	int		fd_out_backup;
	int		exit_status = 0;

	fd_out_backup = dup(1);
	fd_in_backup = dup(0);
	if (handle_redir(cmd->io, data) == -1)
	{
		dup2(fd_out_backup, 1);
		dup2(fd_in_backup, 0);
		clear_doc(cmd->io->inputs);
		return (1);
	}
	exit_status = exec_one_cmd(data, cmd);
	clear_doc(cmd->io->inputs);
	dup2(fd_out_backup, 1);
	dup2(fd_in_backup, 0);
	return (exit_status);
}