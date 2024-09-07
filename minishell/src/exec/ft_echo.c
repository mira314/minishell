#include "exec.h"

static int	print_env(char *env_key)
{
	char	*result;

	result = getenv(env_key);
	if (result != 0)
		printf("%s", result);
	return (ft_strlen(env_key));
}

static char	*get_env_key(char *argv)
{
	size_t	size;
	char	*result;

	size = 0;
	while (argv[size] != ' ' && argv[size] != '"' && argv[size] != 0)
		size++;
	result = (char *)malloc(sizeof(char) * size + 1);
	if (result == 0)
		return (0);
	ft_strlcpy(result, argv, size);
	return (result);
}

void	ft_echo(char *str, int n_option)
{
	size_t	i;
	char	*env_key;

	i = 0;
	//printf("%s", str);
	while (str[i])
	{
		if (str[i] == '"')
			i++;
		else if (str[i] == '$' && (str[i + 1] != ' ' && str[i + 1] != '\\' && str[i] != 0))
		{
			env_key = get_env_key(++i);
			if (env_key == 0)
				return ;
			i = i + print_env(env_key);
			free(env_key);
		}
		else
			i = i + printf("%c", str[i]);
	}
	if (n_option == 0)
		printf("\n");
}
