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
SRC=$(addprefix $(SRC_DIR)/, pipex.c pipex_utils.c parse_input.c \
	parse_input_utils.c open_files.c open_pipes.c fork_child_process.c \
	execute_process.c execute_process_utils.c execute_child_process.c)
SRC_BONUS=$(addprefix $(SRC_BONUS_DIR)/, pipex_bonus.c pipex_utils_bonus.c \
	parse_input_bonus.c parse_input_utils_bonus.c open_files_bonus.c \
	open_pipes_bonus.c fork_child_process_bonus.c execute_process_bonus.c \
	execute_process_utils_bonus.c execute_child_process_bonus.c)
OBJECT=$(SRC:.c=.o)
OBJECT_BONUS=$(SRC_BONUS:.c=.o)


ifdef WITH_BONUS
	OBJ = $(OBJECT_BONUS)
else
	OBJ = $(OBJECT)
endif

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT) :
	@$(MAKE) -C ./libft
	cp ./libft/$(LIBFT) .

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

bonus :
	@$(MAKE) WITH_BONUS=1 all

clean :
	@$(MAKE) clean -C ./$(LIBFT_DIR)
	$(RM) $(OBJECT) $(OBJECT_BONUS) $(LIBFT) ./$(LIBFT_DIR)/$(LIBFT)

fclean :
	@$(MAKE) clean
	$(RM) $(NAME)

re :
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re bonus
