#include "exec.h"

void	exec_one_cmd(t_data	*data)
{
	char	*path;

	//test if it's a tool
	if (handles_bultin(data) == SUCCESS)
		return ;
	path = is_in_path_env(data->cmd->cmd, data->env);
	if (path != NULL)
	{
		printf("It is a tool\n");
		return ;
	}
	print_error(data->cmd->cmd, ": command not found\n", 127);
	//test if (built_in)
}
