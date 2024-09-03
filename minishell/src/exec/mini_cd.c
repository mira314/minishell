/****************************************************************/
/*Cette fonction prend comme paramètre une liste d'argument qui */
/*ne doit contenir qu'un seul élément : un chemin relatif ou un */
/*chemin absolue. Elle retourne zero 0 marquant le succes et un */
/*entier différent de zero en cas d'echec                       */
/****************************************************************/
#include "exec.h"

static int	cd_to_home(void)
{
	char	*pwd;

	pwd = getenv("HOME");
	if (pwd != 0)
		return (chdir(pwd));
	return (1);
}

int	mini_cd(char **argv)
{
	int		argc;

	errno = 0;
	if (argv == NULL)
		return (cd_to_home());
	argc = mini_tbl_len(argv);
	if (argc == 0)
		return (cd_to_home());
	else if (argc > 1)
		return (1);
	return (chdir(argv[0]));
}
