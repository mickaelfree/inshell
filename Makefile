MINISHELL = minishell
CFLAGS = -Wall -Wextra -Werror
NORELINK = -MMD -MP
INCLUDE = -I inc -I libft/include
LIBFT = libft/libft.a
LIBS ?= -lreadline -lncurses

PRINTSTART = @printf "\n$(MAGENTA)🔨Compiling minishell🔨$(RESET)\n"
printstart:
	$(PRINTSTART)

MKFILES=src/builtins/builtins.mk\
	src/exec/exec.mk\
	src/parsing/parsing.mk\
	src/signal/signal.mk\
	src/utils/utils.mk

SRCDIR = src
BUILDDIR = obj

SRCS = $(SRCDIR)/main.c

-include $(MKFILES)

OBJS = $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
DEPS = $(OBJS:.o=.d)

MAKEFLAGS += --no-print-directory

.DEFAULT_GOAL = all  # Set default goal to make all

# Base rule
all: printstart $(MINISHELL)

$(MINISHELL): $(OBJS) $(LIBFT)
	@printf "\n$(MAGENTA)🔨Compile exec🔨$(CYAN)\n"
	@printf "$(YELLOW)Compile $(CYAN)$@ $(YELLOW)from $(CYAN)$^$(RESET)\n"
	@$(CC) $(CFLAGS) $(NORELINK) $(INCLUDE) -o $@ $(OBJS) $(LIBS) $(LIBFT)
	@printf "\n$(YELLOW)✅ Build done!$(RESET)\n\n"

$(LIBFT): FORCE
	@$(MAKE) -C ./libft

# Relink prevention for linked projects
FORCE:
# Individual source file rule
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(GREEN)🔨Compiling $(CYAN) $@ $(GREEN)from $(CYAN)$<"
	@$(CC) $(CFLAGS) $(NORELINK) $(INCLUDE) -o $@ -c $<
	@printf "$(RESET)\n"

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

re: fclean all

# Compile for valgrind
debug: CFLAGS = -Wall -Wextra -Werror -g3
debug: fclean all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp --trace-children=yes ./minishell

# Compile for debug mode + valgrind
fdebug: CFLAGS = -Wall -Wextra -Werror -g3 -DDEBUG_MODE=1
fdebug: fclean all
	DEBUG_MODE=1 valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp --trace-children=yes ./minishell

# Norminette for source and include
norm:
	norminette src/ inc/

gdb:
	gdb ./$(MINISHELL) -ex "break main"

# Compile for tester from https://github.com/zstenger93/42_minishell_tester
tester: CFLAGS = -Wall -Wextra -Werror -g3 -DTESTER=1
tester: fclean all

-include $(DEPS)

.PHONY: all FORCE clean fclean re debug gdb tester

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
