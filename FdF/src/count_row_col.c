/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_row_col.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:51:35 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/21 22:53:51 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/get_next_line.h"

int	count_row_num(char *file, t_aux *aux)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0) // 파일이 없는 경우
	{
		//perror();
		return (0);
	}
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		(aux->row_num)++;
		free(line);
	}
	return (1);
}

int	count_col_num(char **array)
{
	int cnt;

	cnt = 0;
	while (array[cnt])
		cnt++;
	return (cnt);
}

int	check_col_num(int **col_num, int row_num)
{
	int i;
	int j;

	i = 0;
	while(i < row_num - 1)
	{
		j = i + 1;
		while(j < row_num)
		{
			if ((*col_num)[i] != (*col_num)[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}