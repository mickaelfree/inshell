# Base params
MINISHELL = minishell
CFLAGS = -Wall -Wextra -Werror
NORELINK = -MMD -MP
INCLUDE = -I inc -I libft/include
LIBFT = libft/libft.a
LIBS ?= -lreadline -lncurses

MKFILES=src/builtins/builtins.mk\
	src/exec/exec.mk\
	src/parsing/parsing.mk\
	src/signal/signal.mk\
	src/utils/utils.mk

# Project files structure
SRCDIR = src
BUILDDIR = obj

# Source
SRCS = $(SRCDIR)/main.c

-include $(MKFILES)
# Directory structure for object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Other
MAKEFLAGS += --no-print-directory  # Avoid flooding the console

.DEFAULT_GOAL = all  # Set default goal to make all

# Base rule
.PHONY: all
all: $(MINISHELL)

$(MINISHELL): $(OBJS) $(LIBFT)
	@printf "$(GREY)🔨 "
	$(CC) $(CFLAGS) $(NORELINK) $(INCLUDE) -o $@ $(OBJS) $(LIBS) $(LIBFT)
	@printf "\n $(GREEN)✅ Build done!$(RESET)\n"

$(LIBFT): FORCE
	@$(MAKE) -C ./libft

# Relink prevention for linked projects
.PHONY: FORCE
FORCE:

# Individual source file rule
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@printf "$(GREY)🔨 "
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(NORELINK) $(INCLUDE) -o $@ -c $<
	@printf "$(RESET)"

# Cleaning features
.PHONY: clean fclean
clean:
	@printf "$(RED)🗑️  "
	@$(MAKE) clean -C ./libft > /dev/null
	$(RM) -r $(BUILDDIR)
	@printf "$(RESET)\n"


fclean: clean
	@printf "$(RED)🗑️  "
	@$(MAKE) fclean -C ./libft > /dev/null
	$(RM) $(MINISHELL)
	@printf "$(RESET)\n"

# Clean build
.PHONY: re
re: fclean all

# Debug build
.PHONY: debug
debug: CFLAGS = -Wall -Wextra -Werror -g3 -DDEBUG_MODE=1

debug: fclean all
	DEBUG_MODE=1 valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp --trace-children=yes ./minishell

# Norminette for source and include
.PHONY: norm
norm:
	norminette src/ inc/

.PHONY: gdb
gdb:
	gdb ./$(MINISHELL) -ex "break main"

.PHONY: tester
tester: CFLAGS = -Wall -Wextra -Werror -g3 -DTESTER=1
tester: fclean all

-include $(DEPS)

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
