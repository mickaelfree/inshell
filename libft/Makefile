
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

SRCS =
-include $(MKFILES)

OBJECTS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
DEPS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.d, $(SRCS))

-include $(DEPS)

DIRS := $(sort $(dir $(OBJECTS)))

# Build the library
.PHONY: all
all: $(DIRS) $(NAME)

$(DIRS):
	@mkdir -p $@

# Compile .c to .o
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$(YELLOW)Compiling objects and dependencies... $(GREEN)$@ $(YELLOW)from $(GREEN)$<$(RESET)\n"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJECTS) Makefile
	@printf "$(YELLOW)\nCreating Archive... $(GREEN)$@$(RESET)\n"
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
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
RESET  = \033[0m
