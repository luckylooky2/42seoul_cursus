/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:08:19 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/16 14:08:23 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	rearrange_buffer(char *buf)
{
	int	index;
	int	new_index;

	index = 0;
	new_index = 0;
	if (buf == NULL || buf[index] == '\0')
		return (0);
	while (index < BUFFER_SIZE && buf[index] != '\n' && buf[index] != '\0')
		index++;
	if (buf[index] == '\n')
		index++;
	while (index < BUFFER_SIZE + 1)
	{
		buf[new_index] = buf[index];
		if (buf[index] == '\0')
			break ;
		new_index++;
		index++;
	}
	return (0);
}

static t_list	*make_linked_list(char *buf, t_list *char_lst)
{
	char	*new_char;

	if (buf[0] == '\0')
		return (NULL);
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

static int	check_repeat_or_break(char *buf, int index)
{
	int	i;

	i = 0;
	if (index != 0 && buf[index] == '\0' && buf[index - 1] == '\n')
	{
		while (i < BUFFER_SIZE + 1)
			buf[i++] = 0;
		return (1);
	}
	else if (index != 0 && buf[index] == '\0' && buf[index - 1] != '\n')
	{
		while (i < BUFFER_SIZE + 1)
			buf[i++] = 0;
		return (0);
	}
	else
		return (1);
}

static char	*make_next_line(char **buf, t_list *char_lst, int read_size)
{
	char	*next_line;
	int		lst_len;

	if (*buf == NULL)
		return (NULL);
	lst_len = ft_lstsize(char_lst);
	next_line = (char *)ft_calloc(sizeof(char), (lst_len + 1));
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
	static char	*buf[OPEN_MAX + 1];
	t_list		*char_lst;
	int			index;
	int			read_size;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	char_lst = NULL;
	if (buf[fd] == NULL)
		buf[fd] = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	while (buf[fd] != NULL)
	{
		index = rearrange_buffer(buf[fd]);
		if (buf[fd][0] == '\0')
			read_size = read(fd, buf[fd], BUFFER_SIZE);
		while (index < BUFFER_SIZE && buf[fd][index] != '\0' && read_size != -1)
		{
			char_lst = make_linked_list(&buf[fd][index++], char_lst);
			if (char_lst == NULL || buf[fd][index - 1] == '\n')
				break ;
		}
		if (char_lst == NULL || check_repeat_or_break(buf[fd], index) == 1)
			break ;
	}
	return (make_next_line(&buf[fd], char_lst, read_size));
}
