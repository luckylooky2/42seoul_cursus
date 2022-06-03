CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

LIB=pipex.a
SRC_DIR=src
SRC_BONUS_DIR=src_bonus
SRC=pipex.c get_next_line.c get_next_line_utils.c ft_split.c pipex_utils.c
SRC_BONUS=pipex2.c get_next_line.c get_next_line_utils.c ft_split.c pipex_utils.c
OBJECT=$(SRC:.c=.o)
OBJECT_BONUS=$(SRC_BONUS:.c=.o)

ifdef WITH_BONUS
	NAME=pipex2
	OBJ = $(OBJECT_BONUS)
	DIR = $(SRC_BONUS_DIR)
else
	NAME=pipex
	OBJ = $(OBJECT)
	DIR = $(SRC_DIR)
endif

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

all : $(NAME)

bonus :
	@$(MAKE) WITH_BONUS=1 all

clean :
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
