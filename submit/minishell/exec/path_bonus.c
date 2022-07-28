/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:59:43 by gyyu              #+#    #+#             */
/*   Updated: 2022/07/28 15:57:11 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	**path_check(char *env)
{
	int		i;
	char	**path;
	char	*temp;

	if (env == NULL)
		env = "";
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
	char		*path_cmd;
	struct stat	full_name;
	int			path_stat;
	int			i;

	i = 0;
	path_cmd = NULL;
	path_stat = -1;
	while (path_stat == -1 && s->path[i])
	{
		path_cmd = ft_strjoin(s->path[i++], cmd);
		if (path_cmd == NULL)
			panic_memory();
		path_stat = stat(path_cmd, &full_name);
	}
	if (path_stat == -1)
	{
		free(path_cmd);
		return (cmd);
	}
	return (path_cmd);
}
