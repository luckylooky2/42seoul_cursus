CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

NAME=pipex
LIBFT=libft.a
SRC_DIR=src
SRC_BONUS_DIR=src_bonus
LIBFT_DIR=libft
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
	$(CC) -g $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT) :
	@$(MAKE) -C ./libft
	cp ./libft/$(LIBFT) .

%.o : %.c
	$(CC) -g -c $< -o $@

all : $(NAME)

bonus :
	@$(MAKE) WITH_BONUS=1 all

clean :
	@$(MAKE) clean -C ./$(LIBFT_DIR)
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean :
	@$(MAKE) clean
	$(RM) $(NAME) $(LIBFT) ./$(LIBFT_DIR)/$(LIBFT)

re :
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re bonus
