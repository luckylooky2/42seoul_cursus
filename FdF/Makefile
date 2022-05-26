CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
RM=rm -f

MLX=libmlx.a
SRC_DIR=src
SRC_BONUS_DIR=src_bonus
SRC=$(addprefix $(SRC_DIR)/, fdf.c read_map.c fdf_utils.c ft_split.c \
	get_next_line.c get_next_line_utils.c count_row_col.c coordinates.c \
	)
SRC_BONUS=$(addprefix $(SRC_BONUS_DIR)/,)
OBJECT=$(SRC:.c=.o)
OBJECT_BONUS=$(SRC_BONUS:.c=.o)
EXE=fdf

ifdef WITH_BONUS
	NAME=checker
	FILE=checker_bonus
	OBJ = $(OBJECT) $(OBJECT_BONUS)
	DIR = $(SRC_BONUS_DIR)
else
	NAME=fdf
	FILE=fdf
	OBJ = $(OBJECT)
	DIR = $(SRC_DIR)
endif

$(NAME) : $(OBJ) $(MLX)
	$(CC) -g -Lmlx -lmlx -framework OpenGL -framework AppKit $(MLX) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) -g -c $< -o $@

$(MLX) :
	@make -C mlx/
	@cp mlx/$@ .

all : $(NAME)

bonus :
	@$(MAKE) all
	@$(MAKE) WITH_BONUS=1 all

clean :
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean : clean
	$(RM) $(EXE) $(MLX)

re : fclean all

.PHONY : all clean fclean re bonus
