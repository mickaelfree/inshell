NAME = inshell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes

# Sources
SRC_DIR = src/
SRCS = main.c \
        $(SRC_DIR)utils/ft_split.c \
        $(SRC_DIR)utils/str_utils.c \
	$(SRC_DIR)utils/ft_is.c \
        $(SRC_DIR)builtins/echo.c \
        $(SRC_DIR)builtins/pwd.c \
        $(SRC_DIR)builtins/cd.c \
        $(SRC_DIR)builtins/env.c \
        $(SRC_DIR)builtins/unset.c \
        $(SRC_DIR)builtins/export.c \
        $(SRC_DIR)builtins/exit.c \
	$(SRC_DIR)exec/execute.c \
	$(SRC_DIR)exec/utils.c \
	#$(SRC_DIR)exec/pipex.c \
	$(SRC_DIR)exec/find_path.c \
       # $(SRC_DIR)core/cleanup.c \
       # $(SRC_DIR)parsing/parser_map.c \
       # $(SRC_DIR)parsing/checker.c \
       # $(SRC_DIR)parsing/utils_parser.c \
       # $(SRC_DIR)graphics/draw.c \
       # $(SRC_DIR)graphics/pixel_put.c \
       # $(SRC_DIR)graphics/transformations.c \
       # $(SRC_DIR)events/handle_key.c \
       # $(SRC_DIR)utils/get_next_line.c \
       # $(SRC_DIR)utils/memory.c \
       # $(SRC_DIR)utils/get_next_line_utils.c \
       # $(SRC_DIR)utils/ft_split.c \
       # $(SRC_DIR)utils/ft_atoi.c \
       # $(SRC_DIR)utils/ft_strlcpy.c \
       # $(SRC_DIR)utils/ft_strcmp.c \
       # $(SRC_DIR)utils/ft_strrchr.c \
       # $(SRC_DIR)utils/ft_isutils.c \

# Objects
OBJ_DIR = obj/
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Libraries
#MLX_DIR = libs/mlx/
#MLX = $(MLX_DIR)libmlx.a

# Includes
#INCLUDES = -I./includes -I$(MLX_DIR)

# Libraries flags
#LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -lreadline $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile ./includes/inshell.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS)  $(INCLUDES) -c $< -o $@

run: all
	./$(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(MLX_DIR) clean

fclean: clean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

