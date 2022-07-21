# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 19:18:22 by youhan            #+#    #+#              #
#    Updated: 2022/07/20 12:31:08 by hangokim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= 	cc
CFLAGS		= 	-g3 -Wall -Wextra -Werror -DDEBUG_MODE
LFT_DIR		:= 	./libft
LRL_DIR		:= 	/Users/$(shell users)/.brew/opt/readline
BT_DIR		:= 	./builtins
UTIL_DIR	:=	./utils
EC_DIR		:=	./exec
PARSE_DIR	:= ./parsing
LIBS		:= 	-L$(LRL_DIR)/lib -lreadline -L$(LFT_DIR) -lft
INCS		:= 	-I$(LRL_DIR)/include -I$(LFT_DIR) -I.
BT_SRCS		:= 	.c cd.c echo.c env.c export.c pwd.c unset.c subshell.c
UTIL_SRCS	:= 	env_dict.c error_exit.c signal.c delete_funcs1.c delete_funcs2.c \
				global_status.c directory.c regex_matcher.c cleanup_deque.c
EC_SRCS		:=	do_exec.c make_proc_pipe.c path.c play_cmd.c
PARSE_SRCS	:=	break_semicolon.c break_linker.c break_pipe.c break_space.c \
				make_meaning.c make_syntax.c make_piped_commands.c \
				make_expansion_env.c make_expansion_asterisk.c \
				check_parsing_result1.c check_parsing_result2.c
				# del_quotes.c count_bracket.c init_bracket.c del_semicolon.c \
				# parsing_utils.c parsing_utils_2.c del_operator.c push_operator.c \
				# del_pipe.c push_pipe.c push_space.c del_space.c parsing_utils_3.c \
				# parsing_error_check.c parsing_error.c del_backslash.c parsing_error_check_2.c
SRCS		:=	minishell.c \
				test_module.c \
				$(BT_SRCS:%.c=$(BT_DIR)/do_builtin_%.c) \
				$(ENV_SRCS:%.c=$(ENV_DIR)/%.c) \
				$(PARSE_SRCS:%.c=$(PARSE_DIR)/%.c) \
				$(EC_SRCS:%.c=$(EC_DIR)/%.c) \
				$(UTIL_SRCS:%.c=$(UTIL_DIR)/%.c)
				# parsing_after/del_quotes_after.c parsing_after/env_expansion.c
OBJS		:= $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	# make -C $(LFT_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(INCS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean :
	# make clean -C $(LFT_DIR)
	rm -f $(OBJS)

fclean: clean
	# make fclean -C $(LFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus
