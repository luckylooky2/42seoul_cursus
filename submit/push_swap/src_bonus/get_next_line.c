/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 20:33:25 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/08 15:52:25 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static t_list	*make_linked_list(char *buf, t_list *char_lst)
{
	char	*new_char;

	new_char = (char *)malloc(sizeof(char));
	if (new_char == NULL)
	{
		ft_lstclear(&char_lst, free);
		return (NULL);
	}
	*new_char = *buf;
	make_new_node(&char_lst, new_char);
	return (char_lst);
}

static int	check_repeat_or_break(char *buf, int *index, int read_size)
{
	if (*index == read_size && buf[*index - 1] == '\n' && read_size > 0)
	{
		*index = 0;
		return (1);
	}
	else if (*index == read_size && read_size > 0)
	{
		*index = 0;
		return (0);
	}
	else
		return (1);
}

static char	*copy_linked_list(t_list *char_lst, char *next_line)
{
	int	i;

	i = 0;
	while (char_lst)
	{
		next_line[i++] = *((char *)((char_lst)->content));
		char_lst = (char_lst)->next;
	}
	next_line[i] = '\0';
	return (next_line);
}

static char	*make_next_line(char **buf, t_list *char_lst, int read_size)
{
	char	*next_line;
	int		lst_len;

	if (*buf == NULL)
		return (NULL);
	lst_len = ft_lstsize(char_lst);
	next_line = (char *)malloc(sizeof(char) * (lst_len + 1));
	if (next_line == NULL || read_size == -1)
		ft_lstclear(&char_lst, free);
	if (char_lst == NULL || read_size == -1)
		free(next_line);
	if (next_line == NULL || char_lst == NULL || read_size == -1)
	{
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	next_line = copy_linked_list(char_lst, next_line);
	ft_lstclear(&char_lst, free);
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	static int	index;
	static int	read_size;
	t_list		*char_lst;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	char_lst = NULL;
	if (buf == NULL)
		buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	while (buf != NULL)
	{
		if (index == 0)
			read_size = read(fd, buf, BUFFER_SIZE);
		while (index < read_size)
		{
			char_lst = make_linked_list(&buf[index++], char_lst);
			if (char_lst == NULL || buf[index - 1] == '\n')
				break ;
		}
		if (char_lst == NULL || check_repeat_or_break(buf, &index, read_size))
			break ;
	}
	return (make_next_line(&buf, char_lst, read_size));
}
