# Base params
MINISHELL = minishell
CFLAGS = -Wall -Wextra -Werror
NORELINK = -MMD -MP
INCLUDE = -I inc -I libft/include
LIBFT = libft/libft.a
LIBS ?= -lreadline -lncurses

# Project files structure
SRCDIR = src
BUILDDIR = obj

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
	$(SRCDIR)/exec/execute.c \
	$(SRCDIR)/exec/execute_cmd.c \
	$(SRCDIR)/exec/heredoc.c \
	$(SRCDIR)/exec/find_path.c \
	$(SRCDIR)/exec/pipeline_utils.c \
	$(SRCDIR)/exec/pipeline_exec.c \
	$(SRCDIR)/exec/redirections.c \
	$(SRCDIR)/exec/utils_redir.c \
	$(SRCDIR)/parsing/build_pipeline.c \
	$(SRCDIR)/parsing/can_token.c \
	$(SRCDIR)/parsing/expand_env.c \
	$(SRCDIR)/parsing/expand_sizer.c \
	$(SRCDIR)/parsing/expand_utils.c \
	$(SRCDIR)/parsing/expand_quoted.c \
	$(SRCDIR)/parsing/handle_token.c \
	$(SRCDIR)/parsing/identify_token.c \
	$(SRCDIR)/parsing/parsing.c \
	$(SRCDIR)/parsing/quote_handler.c \
	$(SRCDIR)/parsing/redirection_handler.c \
	$(SRCDIR)/parsing/redirection_utils.c \
	$(SRCDIR)/parsing/token_utils.c \
	$(SRCDIR)/signal/handler.c \
	$(SRCDIR)/utils/debug/display_parsed_command.c \
	$(SRCDIR)/utils/debug/print_error.c \
	$(SRCDIR)/utils/debug/print_token.c \
	$(SRCDIR)/utils/ft_free/ft_free_args_and_redir.c \
	$(SRCDIR)/utils/ft_free/ft_free_commands.c \
	$(SRCDIR)/utils/ft_free/ft_free_env.c \
	$(SRCDIR)/utils/ft_free/ft_free_token_list.c \
	$(SRCDIR)/utils/ft_free/ft_free.c \
	$(SRCDIR)/utils/is_char/is_append.c \
	$(SRCDIR)/utils/is_char/is_double_quote.c \
	$(SRCDIR)/utils/is_char/is_escape.c \
	$(SRCDIR)/utils/is_char/is_heredoc.c \
	$(SRCDIR)/utils/is_char/is_operator.c \
	$(SRCDIR)/utils/is_char/is_pipe.c \
	$(SRCDIR)/utils/is_char/is_quote.c \
	$(SRCDIR)/utils/is_char/is_redir.c \
	$(SRCDIR)/utils/is_char/is_single_quote.c \
	$(SRCDIR)/utils/is_char/is_special.c \
	$(SRCDIR)/utils/is_char/is_whitespace.c \
	$(SRCDIR)/utils/skip/skip_charset.c \
	$(SRCDIR)/utils/skip/skip_whitespace.c \
	$(SRCDIR)/utils/char_utils.c \
	$(SRCDIR)/utils/ft_error.c \
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
