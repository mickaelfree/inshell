
# VARIABLES
NAME = libft.a

CC = cc
AR = ar -rcs
OPTIMIZATION ?= -O3

OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = include/
DEP_DIR = dep/

CFLAGS ?= -Wall -Wextra -Werror -MMD $(OPTIMIZATION) -mavx2 -I $(INC_DIR)

SRCS =	char/ft_isalpha.c \
        char/ft_isdigit.c \
        char/ft_isalnum.c \
        char/ft_isascii.c \
        char/ft_isprint.c \
		char/ft_toupper.c \
        char/ft_tolower.c \
\
		convert/ft_atof.c \
		convert/ft_atoi.c \
		convert/ft_itoa.c \
\
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
\
		list/ft_lstnew.c \
		list/ft_lstadd_front.c \
		list/ft_lstsize.c \
		list/ft_lstlast.c \
		list/ft_lstadd_back.c \
		list/ft_lstdelone.c \
		list/ft_lstclear.c \
		list/ft_lstiter.c \
		list/ft_lstmap.c \
\
        memory/ft_bzero.c \
		memory/ft_calloc.c \
        memory/ft_memcpy.c \
		memory/ft_memchr.c \
        memory/ft_memcmp.c \
        memory/ft_memmove.c \
        memory/ft_memset.c \
\
		printf/ft_printf_parse.c \
		printf/ft_printf_utils.c \
		printf/ft_printf.c \
\
		strings/ft_split.c \
        strings/ft_strchr.c \
		strings/ft_strdup.c \
		strings/ft_strndup.c \
		strings/ft_striteri.c \
		strings/ft_strjoin.c \
        strings/ft_strlcat.c \
        strings/ft_strlcpy.c \
        strings/ft_strlen.c \
		strings/ft_strmapi.c \
        strings/ft_strncmp.c \
        strings/ft_strnstr.c \
        strings/ft_strrchr.c \
		strings/ft_strtrim.c \
		strings/ft_substr.c \
\
		time/ft_time_manager.c \
\
		write/ft_putchar_fd.c \
		write/ft_putendl_fd.c \
		write/ft_putnbr_fd.c \
		write/ft_putstr_fd.c

OBJECTS = ${patsubst %.c,$(OBJ_DIR)%.o, $(SRCS)}
DEPS = $(patsubst %.c,$(OBJ_DIR)%.d, $(SRCS))
-include $(DEPS)

# Build the library
.PHONY: all
all: $(NAME)

# Creating all directories
%/:
	@echo "$(YELLOW)Creating directory $(GREEN)$@$(RESET)"
	@mkdir -p $@

# Compile .c to .o
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "$(YELLOW)Compiling objects and dependencies... $(GREEN)$@ $(YELLOW)from $(GREEN)$<$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJ_DIR) $(OBJECTS) Makefile
	@echo "$(YELLOW)\nCreating Archive... $(GREEN)$@$(RESET)\n"
	@$(AR) $@ $(OBJECTS)
	@ranlib $(NAME)

.PHONY: bonus
bonus:
	@echo "$(GREEN)Adding bonuses to library...$(RESET)"
	@$(MAKE) --no-print-directory all SRCS="$(SRCS) $(SRCBONUS)"

# Clean part
.PHONY: clean
clean:
	@echo "$(RED)Cleaning... \n$(YELLOW)Removing $(RED)$(OBJ_DIR)$(RESET)"
	@rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	@echo "$(YELLOW)Removing $(RED)$(NAME)$(RESET)\n"
	@rm -rf $(NAME)

.PHONY: re
re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

.DEFAULT_GOAL = all
# COLORS
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
RESET  = \033[0m
