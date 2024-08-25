/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:30:04 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/25 10:32:04 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSE_H
# define PARSE_H

# include "../../lib/libft/libft.h"
# include "../exec/exec.h"

/*************mini_commande_parse.c**************/
int is_built_in_cmd(char *cmd);
void exec_mini_built(char *cmd);

#endif

