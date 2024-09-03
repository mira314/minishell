/****************************************************************/
/*Cette fonction prend comme paramètre une liste d'argument qui */
/*ne doit contenir qu'un seul élément : un chemin relatif ou un */
/*chemin absolue. Elle retourne zero 0 marquant le succes et un */
/*entier différent de zero en cas d'echec                       */
/****************************************************************/
#include "exec.h"

int	mini_cd(char **argv)
{
	int		argc;
	char	*pwd;

	argc = mini_tbl_len(argv);
	errno = 0;
	if (argc == 0)
	{
		pwd = getenv("HOME");
		if (pwd != 0)
			return (chdir(pwd));
		return (0);
	}
	else if (argc > 1)
		return (1);
	return (chdir(argv[0]));
}
