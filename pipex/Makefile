CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

LIBFT=libft.a
NAME=pipex
SRC_DIR=src
SRC_BONUS_DIR=src_bonus
SRC=$(addprefix $(SRC_DIR)/, pipex.c pipex_utils.c)
SRC_BONUS=$(addprefix $(SRC_DIR)/, pipex.c)
OBJECT=$(SRC:.c=.o)
OBJECT_BONUS=$(SRC_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ = $(OBJECT_BONUS)
else
	OBJ = $(OBJECT)
endif

$(NAME) : $(OBJ) $(LIBFT) 
	# @(MAKE) -C ./libft
	$(CC) -g $(OBJ) $(LIBFT) -o $(NAME)

%.o : %.c
	$(CC) -g -c $< -o $@

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
