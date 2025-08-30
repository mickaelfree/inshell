# Base params
MINISHELL = minishell
CFLAGS = -Wall -Wextra -Werror
NORELINK = -MMD -MP
INCLUDE = -I inc -I libft/include
LIBFT = libft/libft.a
LIBS ?= -lreadline -lncurses

# Project files structure
SRCDIR = src
BUILDDIR = build

# Source
SRCS = $(SRCDIR)/main.c \
	$(SRCDIR)/builtins/simple_builtin.c \
	$(SRCDIR)/exec/exec.c \
	$(SRCDIR)/parsing/ast.c \
	$(SRCDIR)/parsing/parsing.c \
	$(SRCDIR)/utils/debug_ast.c \
	$(SRCDIR)/utils/error.c \
	$(SRCDIR)/utils/utils.c

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
	@echo -n "\n\033[3;90m🔨 "
	$(CC) $(CFLAGS) $(NORELINK) $(INCLUDE) -o $@ $(OBJS) $(LIBS) $(LIBFT)
	@echo -n "\033[0m \n \033[32;40;1m✅ Build done!\033[0m\n"

$(LIBFT): FORCE
	@$(MAKE) -C ./libft

# Relink prevention for linked projects
.PHONY: FORCE
FORCE:

# Individual source file rule
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo -n "\033[3;90m🔨 "
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(NORELINK) $(INCLUDE) -o $@ -c $<
	@echo -n "\033[0m"

# Cleaning features
.PHONY: clean fclean
clean:
	@echo -n "\033[1;91m🗑️  "
	@$(MAKE) clean -C ./libft > /dev/null
	$(RM) -r $(BUILDDIR)
	@echo -n "\033[0m\n"

fclean: clean
	@echo -n "\033[1;91m🗑️  "
	@$(MAKE) fclean -C ./libft > /dev/null
	$(RM) $(MINISHELL)
	@echo -n "\033[0m\n"

# Clean build
.PHONY: re
re: fclean all

# Debug build
.PHONY: debug
debug: CFLAGS = -Wall -Wextra -g3
debug: all

# Norminette for source and include
.PHONY: norm norminette
norm:
	norminette src/ inc/
norminette: norm

-include $(DEPS)
