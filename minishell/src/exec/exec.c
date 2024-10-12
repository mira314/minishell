#include "exec.h"

void	exec_one_cmd(t_data	*data)
{
	char	*path;
	char	*total_path;
	int		pid;
	int		status;

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
		pid = fork();
		if (pid == 0)
		{
			if(execve(total_path, data->cmd->args, data->env) == -1)
				free(total_path);
		}else
		{
			wait(&status);
			g_last_val = WEXITSTATUS(status);
			free(total_path);
		}
		return ;
	}
	print_error(data->cmd->cmd, ": command not found\n", 127);
}
