/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:08:52 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/17 22:33:10 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/get_next_line.h"

int	count_tmp(char **tmp)
{
	int i;

	i = 0;
}

int	read_map(char *argv[], t_aux *aux)
{
	int		fd;
	int		i;
	char	*line;
	int		line_num;

	i = 0;
	line_num = 0;
	fd = open(argv[1], O_RDONLY);
	//if (fd < 0)
		// 에러메시지 띄우기
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line_num++;
		free(line);
	}
	fd = open(argv[1], O_RDONLY);
	aux->map = (char **)malloc(sizeof(char *) * (line_num + 1));
	if (aux->map == NULL)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		aux->lines[i++] = line;
	}
	*(aux->data) = (t_data **)malloc(sizeof(t_data *) * line_num);
	i = 0;
	char **tmp;
	int j;
	int atoi;
	int num;
	while (aux->lines[i])
	{
		j = 0;
		num = 0;
		tmp = ft_split(aux->lines[i], ' ');
		num = count_tmp(tmp);
		while (tmp[j])
		{
			atoi = ft_atoi(tmp[j]);
			j++;
		}
		aux->col_ary[i] = num;
		i++;
		free_double_array(&tmp);
	}
	return (1);
}

void	init_aux(t_aux	*aux)
{
	aux->lines = NULL;
	aux->map = NULL;
	aux->col_ary = NULL;
	aux->data = NULL;
}

int	main(int argc, char *argv[])
{
	t_aux	aux;

	if (argc != 2)
		exit(EXIT_FAILURE);
	init_aux(&aux);
	if (read_map(argv, &aux) == 0)	
	return (0);
}
