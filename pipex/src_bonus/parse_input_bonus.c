/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:39:27 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/11 19:12:30 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static char	*join_path_cmd(t_aux *aux, char **path_ary, int i, int j)
{
	char	*path;

	path = NULL;
	if (j == 0)
		path = ft_strjoin(&(path_ary[j][5]), "/");
	else
		path = ft_strjoin(path_ary[j], "/");
	if (path == NULL)
		exit(EXIT_FAILURE);
	path = ft_strjoin_free(&path, aux->exec_param[i][0], 0);
	if (path == NULL)
		exit(EXIT_FAILURE);
	return (path);
}

static int	check_access(t_aux *aux, char *path, int i, int nth)
{
	if (nth == 1)
	{
		if (access(aux->exec_param[i][0], F_OK) == 0)
		{
			aux->path[i] = ft_strdup(aux->exec_param[i][0]);
			return (0);
		}
	}
	else if (nth == 2)
	{
		if (access(path, F_OK) == 0)
		{
			aux->path[i] = path;
			return (0);
		}
	}
	return (-1);
}

static void	access_path(t_aux *aux, char **path_ary, int path_num)
{
	int		i;
	int		j;
	char	*path;

	i = -1;
	path = NULL;
	while (aux->exec_param[++i])
	{
		j = -1;
		while (path_ary[++j])
		{
			if (check_access(aux, path, i, 1) == 0
				|| aux->exec_param[i][0][0] == '/')
				break ;
			path = join_path_cmd(aux, path_ary, i, j);
			if (check_access(aux, path, i, 2) == 0)
				break ;
			free(path);
		}
		if (j == path_num || aux->exec_param[i][0][0] == '/')
			aux->path[i] = ft_strdup(aux->exec_param[i][0]);
		if (aux->path[i] == NULL)
			exit(EXIT_FAILURE);
	}
}

static void	add_path(t_aux *aux, char *envp[])
{
	char	**path_ary;
	int		path_loc;
	int		path_num;

	path_num = 0;
	path_loc = find_path(envp);
	if (path_loc == -1)
		exit(EXIT_FAILURE);
	path_ary = ft_split(envp[path_loc], ':');
	if (path_ary == NULL)
		exit(EXIT_FAILURE);
	while (path_ary[path_num])
		path_num++;
	access_path(aux, path_ary, path_num);
	free_path(&path_ary);
}

void	parse_input(char *argv[], char *envp[], t_aux *aux)
{
	int	i;

	i = 0;
	aux->exec_param = (char ***)ft_calloc(sizeof(char **), aux->cmd_num + 1);
	aux->path = (char **)ft_calloc(sizeof(char *), aux->cmd_num + 1);
	if (aux->exec_param == NULL || aux->path == NULL)
		exit(EXIT_FAILURE);
	while (i < aux->cmd_num)
	{
		if (aux->here_doc == 0)
			aux->exec_param[i] = ft_split(argv[i + 2], ' ');
		else
			aux->exec_param[i] = ft_split(argv[i + 3], ' ');
		if (aux->exec_param[i] == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
	add_path(aux, envp);
}
