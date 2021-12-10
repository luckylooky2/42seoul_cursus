/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:11:25 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/09 18:38:41 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	rearrange_string(char *buf)
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

static int	check_repeat_break(char *buf, int index)
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

static char	*make_new_string(char **buf, int fd, t_list *char_lst, int index)
{
	char	*new_str;
	int		lst_len;

	if (buf[fd] == NULL)
		return (NULL);
	lst_len = ft_lstsize(char_lst);
	new_str = (char *)ft_calloc(sizeof(char), (lst_len + 1));
	if (new_str == NULL)
		ft_lstclear(&char_lst, free);
	if (char_lst == NULL)
		free(new_str);
	if (new_str == NULL || char_lst == NULL)
	{
		free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	new_str = copy_linked_list(char_lst, new_str);
	ft_lstclear(&char_lst, free);
	if (buf[fd][index] == '\0')
	{
		free(buf[fd]);
		buf[fd] = NULL;
	}
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*buf[10241];
	t_list		*char_lst;
	int			index;
	int			read_size;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	char_lst = NULL;
	if (buf[fd] == NULL)
		buf[fd] = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	while (buf[fd] != NULL)
	{
		index = rearrange_string(buf[fd]);
		if (buf[fd][0] == '\0')
			read_size = read(fd, buf[fd], BUFFER_SIZE);
		while (index < BUFFER_SIZE && buf[fd][index] != '\0' && read_size != -1)
		{
			char_lst = make_linked_list(&buf[fd][index++], char_lst);
			if (char_lst == NULL || buf[fd][index - 1] == '\n')
				break ;
		}
		if (char_lst == NULL || check_repeat_break(buf[fd], index) == 1)
			break ;
	}
	return (make_new_string(buf, fd, char_lst, index));
}
