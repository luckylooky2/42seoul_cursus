/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:39:45 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 14:51:28 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	rollback_meaningless_space(char **argv)
{
	int	i;

	while (*argv)
	{
		i = 0;
		while (*(*argv + i))
		{
			if (*(*argv + i) == -1)
				*(*argv + i) = ' ';
			i++;
		}
		argv++;
	}
}

char	**break_space(t_syntax *s)
{
	char	**argv;
	int		i;
	int		len;

	i = 0;
	while (s->input[i])
	{
		// 의미 없는 공백은 -1로 치환 : split을 피하기 위해
		if (s->input[i] == ' ' && s->meaning[i] != 1)
			s->input[i] = -1;
		// 의미없는 문자들은 삭제(앞으로 당김)
		else if (s->meaning[i] == 1 && (s->input[i] == '\"' || s->input[i] == '\'' || s->input[i] == '\\'))
		{
			len = ft_strlen(s->input + i);
			ft_memmove(s->input + i, s->input + i + 1, len);
			ft_memmove(s->meaning + i, s->meaning + i + 1, len -1);
			continue;
		}
		i++;
	}
	argv = ft_split(s->input, ' ');
	if (argv == NULL)
		panic_memory();
	rollback_meaningless_space(argv);
	return (argv);
}