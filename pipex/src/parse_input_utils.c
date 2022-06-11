/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:54:29 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/11 19:02:03 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	find_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P')
			if (envp[i][1] == 'A')
				if (envp[i][2] == 'T')
					if (envp[i][3] == 'H')
						if (envp[i][4] == '=')
							return (i);
		i++;
	}
	return (-1);
}

void	free_path(char ***path_ary)
{
	int	i;

	i = 0;
	while ((*path_ary)[i])
	{
		free((*path_ary)[i]);
		i++;
	}
	free(*path_ary);
}
