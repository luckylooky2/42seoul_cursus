/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:19:11 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/12 16:19:15 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

typedef struct s_multi_list
{
	int				fd_num;
	char			*buf;
	void			*content;
	struct s_list	*next;
}					t_multi_list;

char	*get_next_line(int fd);
t_multi_list	*make_new_node(t_multi_list **linked_lst, void *content, int case, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_lstsize(t_multi_list *lst);
void	ft_lstclear(t_multi_list **lst, void (*del)(void *));

#endif
