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
	$(SRCDIR)/builtins/isbuiltin.c \
    $(SRCDIR)/builtins/echo.c \
    $(SRCDIR)/builtins/pwd.c \
    $(SRCDIR)/builtins/cd.c \
    $(SRCDIR)/builtins/env.c \
    $(SRCDIR)/builtins/unset.c \
    $(SRCDIR)/builtins/export.c \
    $(SRCDIR)/builtins/exit.c \
	$(SRCDIR)/exec/execute_ast.c \
	$(SRCDIR)/exec/execute.c \
	$(SRCDIR)/exec/execute_cmd.c \
	$(SRCDIR)/exec/heredoc.c \
	$(SRCDIR)/exec/find_path.c \
	$(SRCDIR)/parsing/ast_utils.c \
	$(SRCDIR)/parsing/ast.c \
	$(SRCDIR)/parsing/parsing.c \
	$(SRCDIR)/oldparsing/identify_token.c \
	$(SRCDIR)/oldparsing/token_utils.c \
	$(SRCDIR)/oldparsing/char_utils.c \
	$(SRCDIR)/oldparsing/parsing.c \
	$(SRCDIR)/oldparsing/build_pipeline.c \
	$(SRCDIR)/oldparsing/expand_env.c \
	$(SRCDIR)/signal/handler.c \
	$(SRCDIR)/utils/debug_ast.c \
	$(SRCDIR)/utils/env.c \
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
	@echo -n "$(GREY)🔨 "
	$(CC) $(CFLAGS) $(NORELINK) $(INCLUDE) -o $@ $(OBJS) $(LIBS) $(LIBFT)
	@echo -n "\n $(GREEN)✅ Build done!$(RESET)\n"

$(LIBFT): FORCE
	@$(MAKE) -C ./libft

# Relink prevention for linked projects
.PHONY: FORCE
FORCE:

# Individual source file rule
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo -n "$(GREY)🔨 "
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(NORELINK) $(INCLUDE) -o $@ -c $<
	@echo -n "$(RESET)"

# Cleaning features
.PHONY: clean fclean
clean:
	@echo -n "$(RED)🗑️  "
	@$(MAKE) clean -C ./libft > /dev/null
	$(RM) -r $(BUILDDIR)
	@echo -n "$(RESET)\n"


fclean: clean
	@echo -n "$(RED)🗑️  "
	@$(MAKE) fclean -C ./libft > /dev/null
	$(RM) $(MINISHELL)
	@echo -n "$(RESET)\n"

# Clean build
.PHONY: re
re: fclean all

# Debug build
.PHONY: debug
debug: CFLAGS = -Wall -Wextra -Werror -g3
debug: all

# Norminette for source and include
.PHONY: norm
norm:
	norminette src/ inc/

.PHONY: gdb
gdb:
	gdb ./$(MINISHELL) -ex "break main"

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