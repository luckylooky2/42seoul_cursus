/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_enums_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:36:34 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 15:55:44 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENUMS_BONUS_H
# define MINISHELL_ENUMS_BONUS_H
# define READ 0
# define WRITE 1

typedef enum e_interactive_status
{
	NOT_INTERACTIVE,
	INTERACTIVE,
	HEREDOC
}	t_int_status;

typedef enum e_subject
{
	MAIN,
	SUB
}	t_subject;

typedef enum e_control
{
	BACKUP_STDIO,
	RESTORE_STDIO
}	t_control;

typedef enum e_heredoc_command
{
	CLOSE_HEREDOC = 0,
	PUT_HEREDOC
}	t_heredoc_cmd;

typedef enum e_delimiter
{
	SEMICOLON = 1,
	AND_AND,
	OR_OR,
	PIPE,
	NO_DELIM,
	PRINTED
}	t_delimiter;

typedef enum e_dir_command
{
	INIT_DIR = 0,
	CLOSE_DIR,
	GET_DIR
}	t_dir_cmd;

typedef enum e_env_command
{
	CLOSE_ENV = 0,
	GET_ENV,
	PUT_ENV,
	DELETE_ENV,
	LIST_ENV
}	t_env_cmd;

typedef enum e_global_command
{
	GET_STATUS = 0,
	SET_STATUS,
	GET_INTERACTIVE,
	SET_INTERACTIVE,
	GET_P_ERROR,
	SET_P_ERROR
}	t_global_cmd;

typedef enum e_parsing_error_status
{
	NO_ERROR = 0,
	OPEN_BRACKET = 1,
	CLOSE_BRACKET,
	OPEN_QUOTE,
	INCOMPLETE,
	MAXIMUM_DEPTH,
}	t_p_e_status;

typedef enum e_quote_status
{
	CLOSED = 0,
	OPEN_D = 34,
	OPEN_S = 39
}	t_q_status;

typedef enum e_link
{
	NONE = 0,
	AND,
	OR
}	t_link;

typedef enum e_builtin
{
	NON_SUPPORTING = 0,
	BLANK,
	EXIT,
	CD,
	ECHO,
	ENV,
	EXPORT,
	PWD,
	SUBSHELL,
	UNSET,
}	t_builtin;

typedef void			(*t_sig_handler)(int);
typedef struct dirent	t_dirent;

#endif