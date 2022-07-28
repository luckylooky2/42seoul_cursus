/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 21:03:06 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/24 18:21:12 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing_error_on_syntax(t_syntax *syntax)
{
	return (there_is_only_one_ampersand(syntax) || \
		there_are_redirection_parsing_error(syntax) || \
		there_are_subshell_parsing_error(syntax) || \
		there_are_parse_error_in_subshell(syntax));
}
