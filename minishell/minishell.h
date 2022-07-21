/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:12:40 by youhan            #+#    #+#             */
/*   Updated: 2022/07/19 20:54:37 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"
# define READ 0
# define WRITE 1

typedef void	(*t_sig_handler)(int);
typedef struct dirent	t_dirent;

typedef enum e_delimiter
{
	SEMICOLON = 1,
	AND_AND,
	OR_OR,
	PIPE
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
	NO_COMMAND,
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

typedef struct s_syntax
{
	char	*input;
	char	*meaning;
}	t_syntax;

typedef struct s_cmd
{
	char	*cmd;
	char	*cmd_mod;
	int		*status[2];
	char	**mod;
	int		**mod_status;
	t_link	**link;
	char	***opr_cmd;
	int		***opr_status;
	char	****p_cmd;
	int		****p_status;
	char	*****s_cmd;
	int		*****s_status;
}	t_cmd;

typedef struct s_result
{
	t_deq	*deque;
}	t_result;


typedef struct s_args
{
	char	**commands;
	char	*input_file;
	char	*output_file;
}	t_args;

/** (final) parsed args structs **/

typedef struct s_command
{
	char	**argv;
	t_deq	*input;
	t_deq	*output;
}	t_command;

typedef struct s_commands
{
	t_syntax	*syntax;
	t_link		prev;
}	t_commands;

/** env structs **/
typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

/** builtin enum **/
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

/** exec struct **/
typedef struct s_state
{
	pid_t	*pid;
	int		**pipes;
	int		pid_cnt;
	int		pipe_cnt;
	char	**path;
	char	builtin_flag;
}	t_state;

int				count_char_pointer_2(char **cmd);
int				count_char_pointer_3(char ***cmd);
int				count_char_pointer_4(char ****cmd);
int				count_char_pointer_5(char *****cmd);
int				bool_conditional_space(char *cmd, int *status, int *bracket, int i);
int				bool_conditional_pipe(char *cmd, int *status, int *bracket, int i);
int				bool_conditional(char *cmd, int *status, int *bracket, int i);
void			init_split(int *i, int *path);
int				check_bracket(char **cmd, int *status);
int				move_space(char *cmd, int *status, int i);

// parsing
int				del_backslash(t_cmd *cmd);
int				split_move(const char *str, int *status, int i);
int				split_move_space(const char *str, int *status, int i);
void			ft_strncpy_int(int *dest, int *src, unsigned int n);
void			ft_strncpy_char(char *dest, char *src, unsigned int n);
int				del_semicolon(t_cmd *cmd);
int				del_quotes(t_cmd *cmd);
int				count_bracket(char *cmd, int *status);
int				find_close_bracket(char *cmd, int *status, int i);
int				init_bracket(char *cmd, int **path, int *status);
int				del_operator(t_cmd *cmd);
char			**push_operator(char *cmd, int *status, int ***opr_s, int *bracket);
int				del_pipe(t_cmd *cmd);
char			**push_pipe(char *cmd, int *status, int ***p_status, int *bracket);
char			**push_space(char *cmd, int *status, int ***p_status, int *bracket);
int				del_space(t_cmd *cmd);
int				ft_count_split(const char *str, int *status);
void			delim_bracket(char *cmd, int *status, int **bracket);
int				count_oprator(char *cmd, int *bracket);
int				skip_operator(char *cmd, int *status, int start, int *bracket);

// parsing_after

int				del_quotes_after(char **cmd, int **status);
int				env_expansion(char **cmd, int **status);
int				del_afer(char ***cmd, int ***cmd_status);
int				pipe_del_expansion(char ***cmd, int	***cmd_status);
// parsing error
int				error_token(t_cmd cmd);
int				error_token_check(char *cmd, int *status);
int				error_token_brackets(char *cmd, int *status);
int				error_token_empty_bracket(char *cmd, int *status);

// print
void			printf_space(t_cmd *cmd);
void			printf_token_error();
void			printf_operator(t_cmd *cmd);
void			printf_split(char **str);
void			printf_split_status(int **str, char **s);
void			printf_data(t_cmd *cmd, int max);
void			printf_pipe(t_cmd *cmd);

/** functions **/
void			do_exec(t_deq *commands);

// utils
void			panic(char *message);
void			panic_memory(void);
void			error_exit(char *str, char *flag);
void			error_handle(char *message);
void			error_errno(void);
char			*env_commands(t_env_cmd cmd, char **argv);
int				global_status(t_global_cmd cmd, int value);
int				regex_matcher(char *input, char *regex);
t_deq			*cleanup_deque(t_deq *deq, void del(void *));
t_dirent		*get_next_dir(t_dir_cmd cmd);

// delete functions
void			delete_linked_commands(void *l_cmd);
void			delete_str_array(void *arr);
void			delete_t_command(void *cmd);
void			delete_t_commands(void *cmd);
void			delete_t_env(void *arg);
void			delete_t_syntax(void *arg);
void			delete_t_state(void *arg);

// signals
t_sig_handler	ft_signal(int signum, t_sig_handler handler);
void			sigint_handler(int signum);
void			sigquit_handler(int signum);

// builtins
t_builtin		get_builtin_enum(char **argv);
void			do_builtin(char **argv);
void			do_builtin_cd(char **argv);
void			do_builtin_echo(char **argv);
void			do_builtin_env(char **argv);
void			do_builtin_export(char **argv);
void			do_builtin_pwd(char **argv);
void			do_builtin_subshell(char **argv);
void			do_builtin_unset(char **argv);
int				is_command_subshell(char *arg);

// exec functions
void			play_cmd(t_state *s, char **env, t_deq *commands);
void			make_proc_pipe(t_state *s);
char			**path_check(char *env);
char			*find_cmd_in_path(t_state *s, char *cmd);

// parsing functions
t_deq			*parse_args(char *input);
char			*make_meaning(char *input);
t_syntax		*syntax_from_input(char *input, char *meaning);
t_syntax		*slice_syntax(t_syntax *s, int i, int length, t_delimiter delimiter);
void			insert_syntax(t_syntax *s1, t_syntax *s2, int i);
int				error_on(t_deq *broken_semicolon);
int				parsing_error_on_syntax(t_syntax *syntax);
t_deq			*break_semicolon(t_syntax *s);
void			break_linker(t_deq *broken_semicolon);
t_deq			*make_piped_commands(t_syntax *syntax);
t_deq			*break_pipe(t_syntax *s);
char			**break_space(t_syntax *syntax);
void			expand_env(t_syntax *s, int i);
void			expand_asterisk(t_syntax *s, int i);

// test modules
char			***test(char *str);
void			print_parsed_arg(t_deq *parsed_arg);
void			print_fd_status(int n, int fd, int flag);
void			print_debug_message(char *str);
void			print_deq_of_syntax(t_deq *deq);
void			print_argv(char **argv);
void			print_piped_commands(t_deq *piped_commands);
void			print_syntax(t_syntax *s);
void			foo(void);

#endif
