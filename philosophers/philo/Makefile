CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
THREAD=-pthread
RM=rm -f

NAME=philo
SRC_DIR=src
SRC_BONUS_DIR=src_bonus
SRC=$(addprefix $(SRC_DIR)/, philosophers.c ft_split.c philosophers_utils.c \
	parse_input.c init.c malloc.c print.c thread.c thread_routine.c \
	monitor.c action.c )
SRC_BONUS=$(addprefix $(SRC_BONUS_DIR)/, )
OBJECT=$(SRC:.c=.o)
OBJECT_BONUS=$(SRC_BONUS:.c=.o)


ifdef WITH_BONUS
	OBJ = $(OBJECT_BONUS)
else
	OBJ = $(OBJECT)
endif

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -g $(THREAD) -o $(NAME)

%.o : %.c
	$(CC) -c -g $< $(THREAD) -o $@

all : $(NAME)

bonus :
	@$(MAKE) WITH_BONUS=1 all

clean :
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean :
	@$(MAKE) clean
	$(RM) $(NAME)

re :
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re bonus
