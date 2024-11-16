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
		if(execve(path, args, envs) == -1)
		perror(path);
		if (errno == EACCES)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
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
static int	handle_here_doc(int	*fds, char *del, t_term *term)
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
	int		fds[2];

	i = 0;
	while(file[i].filename != 0)
	{
		if (file[i].mode == HEREDOC)
		{
			pipe(fds);
			if (handle_here_doc(fds, file[i].filename, term) == -1)
			{
				close(fds[0]);
				close(fds[1]);
				return (-1);
			}
			close(fds[1]);
			input = fds[0];	
		}
		else if (file[i].mode == INPUT)
		{
			input = open(file[i].filename, O_RDONLY);
			if (input == -1)
			{
				perror(file[i].filename);
				return (-1);
			}
		}
		else
			printf("Unkown input mode\n");
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

static int  on_forking_error_pipe(int *fds)
{
    perror("Forking");
    close_pipe(fds);
    return (1);
}   

static void fork_fun(int *input, int *output, t_data *data, t_cmd *cmd)
{
    if (input != NULL)
    {
        close(input[1]);
        dup2(input[0], 0);
        close(input[0]);
    }
    close(output[0]);
    if (cmd->next != NULL)
        dup2(output[1], 1);
    close(output[1]);
    exec_with_redir(data, cmd);
    exit(0);
}

int    pipe_loop(t_data *data, t_cmd *cmd, int *pipe_in)
{
    int     pipe_out[2];
    int     pid;
    int     status;

    if (pipe(pipe_out) == -1)
    {
        perror("piping");
        return (1);
    }
    pid = fork();
    if (pid == -1)
        on_forking_error_pipe(pipe_out);   
    if (pid == 0)
        fork_fun(pipe_in, pipe_out, data, cmd);
    else
    {
        if (pipe_in != NULL)
            close_pipe(pipe_in);
        if (cmd->next != NULL)
        {
            pipe_loop(data, cmd->next, pipe_out);
            wait(NULL);
        }
        else
        {
            wait(&status);
            if (WIFEXITED(status));
                //printf("%d\n", WEXITSTATUS(status));
            else if(WIFSIGNALED(status))
                printf("Terminated by signal %d\n", WTERMSIG(status));
            fflush(stdout);
        }
    }
	return (0);
}

void	exec(t_data *data)
{
	t_cmd *cmd;

	cmd = data->cmd;
	if (cmd->next == NULL)
		exec_with_redir(data, cmd);
	else
		pipe_loop(data, cmd, NULL);
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
		exit_status = exec_with_fork(cmd->args[cmd->offset], cmd->args + cmd->offset, data->env);
	else
	{
		exit_status = 127;
		print_error(cmd->args[cmd->offset], ": command not found\n", 127);
	}
	return (exit_status);
}

void	exec_with_redir(t_data *data, t_cmd *cmd)
{
	int		fd_in_backup;
	int		fd_out_backup;
	int		exit_status;

	fd_out_backup = dup(1);
	fd_in_backup = dup(0);
	if (handle_redir(cmd->io, data) == -1)
	{
		data->exit_value = 1;
		dup2(fd_out_backup, 1);
		dup2(fd_in_backup, 0);
		printf("exit status : 1\n");
		return ;
	}
	exit_status = exec_one_cmd(data, cmd);
	dup2(fd_out_backup, 1);
	dup2(fd_in_backup, 0);
	data->exit_value = exit_status;
}