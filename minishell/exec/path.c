/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:00:13 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 15:03:51 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// path로 env_list에서 검색한 결과 : env
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