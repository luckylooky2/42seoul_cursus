/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:41:22 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/26 16:44:05 by hangokim         ###   ########.fr       */
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
		if (s->input[i] == ' ' && s->meaning[i] != 1)
			s->input[i] = -1;
		else if (s->meaning[i] == 1 && \
		(s->input[i] == '\"' || s->input[i] == '\'' || s->input[i] == '\\'))
		{
			len = ft_strlen(s->input + i);
			ft_memmove(s->input + i, s->input + i + 1, len);
			ft_memmove(s->meaning + i, s->meaning + i + 1, len - 1);
			continue ;
		}
		i++;
	}
	argv = ft_split(s->input, ' ');
	if (argv == NULL)
		panic_memory();
	rollback_meaningless_space(argv);
	return (argv);
}

char	**break_space_const(t_syntax *s)
{
	int			i;
	char		**argv;
	char		*new_meaning;
	t_syntax	*s_copy;

	new_meaning = ft_strdup(s->input);
	if (new_meaning == NULL)
		panic_memory();
	ft_memcpy(new_meaning, s->meaning, ft_strlen(s->input));
	s_copy = syntax_from_input(s->input, new_meaning);
	i = 0;
	while (s_copy->input[i])
	{
		if (s_copy->input[i] == ' ' && s_copy->meaning[i] != 1)
			s_copy->input[i] = -1;
		i++;
	}
	argv = ft_split(s_copy->input, ' ');
	if (argv == NULL)
		panic_memory();
	rollback_meaningless_space(argv);
	delete_t_syntax(s_copy);
	return (argv);
}
