/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 20:33:46 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/13 20:33:54 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	rearrange_string(t_multi_list *now)
{
	int	index;
	int	new_index;

	index = 0;
	new_index = 0;
	if ((now->buf) == NULL || (now->buf)[index] == '\0')
		return (0);
	while (index < BUFFER_SIZE && (now->buf)[index] != '\n' && (now->buf)[index] != '\0')
		index++;
	if ((now->buf)[index] == '\n')
		index++;
	while (index < BUFFER_SIZE + 1)
	{
		(now->buf)[new_index] = (now->buf)[index];
		if ((now->buf)[index] == '\0')
			break ;
		new_index++;
		index++;
	}
	return (0);
}

static t_multi_list	*make_linked_list(char *buf, t_multi_list *char_lst)
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
	make_new_node(&char_lst, new_char, 0, fd);
	return (char_lst);
}

static int	check_repeat_or_break(t_multi_list *now, int index)
{
	int	i;

	i = 0;
	if (index != 0 && (now->buf)[index] == '\0' && (now->buf)[index - 1] == '\n')
	{
		while (i < BUFFER_SIZE + 1)
			(now->buf)[i++] = 0;
		return (1);
	}
	else if (index != 0 && (now->buf)[index] == '\0' && (now->buf)[index - 1] != '\n')
	{
		while (i < BUFFER_SIZE + 1)
			(now->buf)[i++] = 0;
		return (0);
	}
	else
		return (1);
}

static char	*make_next_line(t_multi_list **fd_lst, t_multi_list *now, t_multi_list *char_lst, int read_size)
{
	int		i;
	char	*next_line;
	t_multi_list	*curr;

	i = 0;
	curr = char_lst;
	if (now == NULL)
		return (NULL);
	next_line = (char *)ft_calloc(sizeof(char), (ft_lstsize(char_lst) + 1));
	if (next_line == NULL || read_size == -1)
		ft_lstclear(&char_lst, free);
	if (char_lst == NULL || now->buf == NULL || read_size == -1)
		free(next_line);
	if (next_line == NULL || char_lst == NULL || now->buf == NULL || read_size == -1)
	{
		ft_lstclear(fd_lst);
		return (NULL);
	}
	while (curr)
	{
		next_line[i++] = *((char *)((curr)->content));
		curr = (curr)->next;
	}
	ft_lstclear(&char_lst, free);
	return (next_line);
}
static t_multi_list	*check_fd(t_multi_list **fd_lst, int fd)
{
	t_multi_list	*new_node;

	while (*fd_lst != NULL)
	{
		if ((*fd_lst)->fd_num == fd)
			return (*fd_lst);
		*fd_lst = (*fd_lst)->next;
	}
	new_node = make_new_node(fd_lst, NULL, 1, fd);
	if (new_node == NULL)
		return (NULL);
	return (check_fd(fd_lst, fd));
}

char	*get_next_line(int fd)
{
	static t_multi_list	*fd_lst;
	t_multi_list		*now;
	t_multi_list		*char_lst;
	int					index;
	int					read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	char_lst = NULL;
	now = check_fd(fd_lst, fd);
	while (now != NULL)
	{
		index = rearrange_string(now->buf);
		if ((now->buf)[0] == '\0')
			read_size = read(fd, now->buf, BUFFER_SIZE);
		while (index < BUFFER_SIZE && (now->buf)[index] != '\0' && read_size != -1)
		{
			char_lst = make_linked_list(&(now->buf)[index++], char_lst);
			if (char_lst == NULL || (now->buf)[index - 1] == '\n')
				break ;
		}
		if (char_lst == NULL || check_repeat_or_break(now, index) == 1)
			break ;
	}
	return (make_next_line(&fd_lst, now, char_lst, read_size));
}
