CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
THREAD=-pthread
RM=rm -f

NAME=philo_bonus
SRC_BONUS_DIR=src_bonus
SRC_BONUS=$(addprefix $(SRC_BONUS_DIR)/, philosophers_bonus.c parse_input_bonus.c \
	init_bonus.c print_bonus.c philosophers_utils_bonus.c malloc_bonus.c \
	execute_process_bonus.c execute_child_process_bonus.c action_bonus.c \
	parse_input_utils.c fork_child_process.c execute_process_utils_bonus.c \
	monitor_bonus.c thread_routine.c )

OBJECT_BONUS=$(SRC_BONUS:.c=.o)

$(NAME) : $(OBJECT_BONUS)
	$(CC) $(OBJECT_BONUS) -g $(THREAD) -o $(NAME)

%.o : %.c
	$(CC) -c -g $< $(THREAD) -o $@

all : $(NAME)

clean :
	$(RM) $(OBJECT_BONUS)

fclean :
	@$(MAKE) clean
	$(RM) $(NAME)

re :
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re
