CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
THREAD=-pthread
RM=rm -f

NAME=philo
SRC_DIR=src
SRC=$(addprefix $(SRC_DIR)/, philosophers.c ft_split.c philosophers_utils.c \
	parse_input.c init.c malloc.c print.c thread.c thread_routine.c \
	monitor.c action.c parse_input_utils.c )
OBJECT=$(SRC:.c=.o)

$(NAME) : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) $(THREAD) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(THREAD) -o $@

all : $(NAME)

clean :
	$(RM) $(OBJECT)

fclean :
	@$(MAKE) clean
	$(RM) $(NAME)

re :
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re
