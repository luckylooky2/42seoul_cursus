/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_in_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:39:10 by gyyu              #+#    #+#             */
/*   Updated: 2022/07/08 16:53:54 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_cmd_in_path(t_state *s, char *cmd)
{
	int		i;
	int		ac;
	char	*path_cmd;

	i = 0;
	ac = -1;
	while (ac == -1 && s->path[i])
	{
		path_cmd = ft_strjoin(s->path[i++], cmd);
		ac = access(path_cmd, F_OK);
	}
	if (ac == -1)
	{
		free(path_cmd);
		return (cmd);
	}
	return (path_cmd);
}
