/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:59:43 by gyyu              #+#    #+#             */
/*   Updated: 2022/07/17 20:44:31 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**path_check(char *env)
{
	int		i;
	char	**path;
	char	*temp;

	path = ft_split(env, ':');
	if (path == NULL)
		panic_memory();
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (temp == NULL)
			panic_memory();
		free(path[i]);
		path[i] = temp;
		i++;
	}
	return (path);
}

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
