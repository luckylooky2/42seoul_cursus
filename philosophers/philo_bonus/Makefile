CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
THREAD=-pthread
RM=rm -f

NAME=philo_bonus
SRC_BONUS_DIR=src_bonus
SRC_BONUS=$(addprefix $(SRC_BONUS_DIR)/, philosophers.c ft_split.c philosophers_utils.c \
	parse_input.c init.c malloc.c print.c thread.c thread_routine.c \
	monitor.c action.c )
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
