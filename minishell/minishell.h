/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:12:40 by youhan            #+#    #+#             */
/*   Updated: 2022/07/27 22:46:56 by chanhyle         ###   ########.fr       */
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
# include "minishell_enums.h"

/** parsing structs **/
typedef struct s_syntax
{
	char	*input;
	char	*meaning;
}	t_syntax;

typedef struct s_data
{
	int		infile_num;
	int		outfile_num;
	int		cmd_num;
	char	*rd_flag;
	char	check;
}	t_data;

typedef struct s_command
{
	t_syntax	*syntax;
	char		**argv;
	t_deq		*input;
	t_deq		*output;
}	t_command;

typedef struct s_commands
{
	t_syntax	*syntax;
	t_deq		*piped_commands;
	t_link		prev;
}	t_commands;

/** env structs **/
typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

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
/** functions **/
void			do_exec(t_deq *commands);
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
t_syntax		*slice_syntax(t_syntax *s, int i, int length, t_delimiter d);
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
void			remove_redirection(t_syntax *syntax, t_command *cmd);
void			assign_redirection_flag(t_syntax *syn, t_data *data);
void			remove_character(t_syntax *syn, t_data *data);
void			parse_redirection(t_syntax *syn, t_data *data, t_command *cmd);

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
