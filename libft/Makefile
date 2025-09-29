
# VARIABLES
NAME = libft.a

CC = cc
AR = ar -rcs
OPTIMIZATION ?= -O2

OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = include/
DEP_DIR = dep/

CFLAGS ?= -Wall -Wextra -Werror -MMD $(OPTIMIZATION) -mavx2 -I $(INC_DIR)

MKFILES = src/char/char.mk\
	src/convert/convert.mk\
	src/gnl/gnl.mk\
	src/list/list.mk\
	src/memory/memory.mk\
	src/mm256/mm256.mk\
	src/printf/printf.mk\
	src/strings/strings.mk\
	src/time/time.mk\
	src/write/write.mk

PRINTSTART = @printf "\n$(MAGENTA)🔨Compiling libft🔨$(RESET)\n"

SRCS =
-include $(MKFILES)

OBJECTS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
DEPS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.d, $(SRCS))

-include $(DEPS)

DIRS := $(sort $(dir $(OBJECTS)))

# Build the library
printstart:
	$(PRINTSTART)

.PHONY: all
all: printstart $(DIRS) $(NAME)

$(DIRS):
	@mkdir -p $@

# Compile .c to .o
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$(YELLOW)🔨Compiling objects and dependencies... $(GREEN)$@ $(YELLOW)from $(GREEN)$<$(RESET)\n"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJECTS) Makefile
	@printf "$(YELLOW)\n✅ Archive Created... $(GREEN)$@$(RESET)\n"
	@$(AR) $@ $(OBJECTS)
	@ranlib $(NAME)

# Clean part
.PHONY: clean
clean:
	@printf "$(RED)Cleaning... \n$(YELLOW)Removing $(RED)$(OBJ_DIR)$(RESET)"
	@rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	@printf "$(YELLOW)Removing $(RED)$(NAME)$(RESET)\n"
	@rm -rf $(NAME)

.PHONY: re
re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

.DEFAULT_GOAL = all

# COLORS
RESET = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
GREY = \033[1;90m
