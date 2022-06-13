CC=cc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Werror -Wextra
MLXFLAGS=-Lmlx -lmlx -framework OpenGL -framework AppKit
RM=rm -f

NAME=fdf
MLX=libmlx.a
SRC_DIR=src
SRC_BONUS_DIR=src_bonus
SRC=$(addprefix $(SRC_DIR)/, fdf.c read_map.c event_functions.c \
	repeat_main_loop.c free_data.c init_data.c fdf_utils.c ft_split.c \
	get_next_line.c get_next_line_utils.c count_row_col.c \
	translate.c project.c rotate.c move.c draw.c)
SRC_BONUS=$(addprefix $(SRC_BONUS_DIR)/, fdf_bonus.c read_map_bonus.c \
	event_functions_bonus.c repeat_main_loop_bonus.c free_data_bonus.c \
	init_data_bonus.c fdf_utils_bonus.c ft_split_bonus.c \
	get_next_line_bonus.c get_next_line_utils_bonus.c count_row_col_bonus.c \
	translate_bonus.c project_bonus.c rotate_bonus.c move_bonus.c draw_bonus.c)
OBJECT=$(SRC:.c=.o)
OBJECT_BONUS=$(SRC_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ = $(OBJECT_BONUS)
else
	OBJ = $(OBJECT)
endif

$(NAME) : $(OBJ) $(MLX)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(MLX) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX) :
	@make -C mlx/
	@cp mlx/$@ .

all : $(NAME)

bonus :
	@$(MAKE) WITH_BONUS=1 all

clean :
	@$(MAKE) clean -C mlx/
	$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean :
	@$(MAKE) clean
	$(RM) $(NAME) $(MLX)

re :
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re bonus
