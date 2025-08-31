# Base params
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
NORELINK = -MMD -MP
INCLUDE = -I include

# Project files structure
SRCDIR = source
BUILDDIR = build

# Libft source
SRCS = $(SRCDIR)/char/char.c \
       $(SRCDIR)/char/case.c \
       $(SRCDIR)/char/space.c \
       $(SRCDIR)/memory/memory1.c \
       $(SRCDIR)/memory/memory2.c \
       $(SRCDIR)/string/comparison.c \
       $(SRCDIR)/string/concatenation.c \
       $(SRCDIR)/string/copy.c \
       $(SRCDIR)/string/measure.c \
       $(SRCDIR)/string/search.c \
       $(SRCDIR)/string/ft_split.c \
       $(SRCDIR)/string/ft_striteri.c \
       $(SRCDIR)/string/ft_strjoin.c \
       $(SRCDIR)/string/ft_strmapi.c \
       $(SRCDIR)/string/ft_strtrim.c \
       $(SRCDIR)/string/ft_substr.c \
       $(SRCDIR)/convert/int-alpha.c \
       $(SRCDIR)/io/put.c \
       $(SRCDIR)/io/get_next_line/get_next_line.c \
       $(SRCDIR)/io/get_next_line/utils.c \
       $(SRCDIR)/io/not_cursed/not_cursed.c \
       $(SRCDIR)/io/not_cursed/footer.c \
       $(SRCDIR)/io/not_cursed/utils.c \
       $(SRCDIR)/data_structures/linked_list/linked_list1.c \
       $(SRCDIR)/data_structures/linked_list/linked_list2.c

# Printf source
PRINTF_SRCS = $(SRCDIR)/io/printf/ft_printf.c \
       $(SRCDIR)/io/printf/ft_dprintf.c \
       $(SRCDIR)/io/printf/ft_sprintf.c \
       $(SRCDIR)/io/printf/ft_printf_internal.c \
       $(SRCDIR)/io/printf/lexer.c \
       $(SRCDIR)/io/printf/lexer_helpers.c \
       $(SRCDIR)/io/printf/nodes/nodes_manager.c \
       $(SRCDIR)/io/printf/nodes/nodes_dump_dispatch.c \
       $(SRCDIR)/io/printf/nodes/nodes_len_dispatch.c \
       $(SRCDIR)/io/printf/nodes/nodes_helpers.c \
       $(SRCDIR)/io/printf/nodes/operations/node_char.c \
       $(SRCDIR)/io/printf/nodes/operations/node_str.c \
       $(SRCDIR)/io/printf/nodes/operations/node_pointer.c \
       $(SRCDIR)/io/printf/nodes/operations/node_int.c \
       $(SRCDIR)/io/printf/nodes/operations/node_int_helpers.c \
       $(SRCDIR)/io/printf/nodes/operations/node_hex.c \
       $(SRCDIR)/io/printf/nodes/operations/node_hex_helpers.c \
       $(SRCDIR)/io/printf/nodes/operations/node_written_count.c \
       $(SRCDIR)/io/printf/nodes/operations/node_percent.c \
       $(SRCDIR)/io/printf/nodes/operations/node_text.c \
       $(SRCDIR)/io/printf/utils/io.c \
       $(SRCDIR)/io/printf/utils/io_utils.c \
       $(SRCDIR)/io/printf/utils/conversion.c \

# Complete source
ALL_SRCS = $(SRCS) $(PRINTF_SRCS)

# Directory structure for object files
OBJS = $(ALL_SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Other
MAKEFLAGS += --no-print-directory  # Avoid flooding the console

.DEFAULT_GOAL = all  # Set default goal to make all

# Base rule
.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@echo -n "\n\033[3;90m🔨 "
	ar rcs $(NAME) $^
	@echo -n "\033[0m \n \033[32;40;1m✅ Done!\033[0m\n"

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
	$(RM) -r $(BUILDDIR)
	@echo -n "\033[0m\n"

fclean: clean
	@echo -n "\033[1;91m🗑️  "
	$(RM) $(NAME)
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
	norminette source/ include/
norminette: norm

-include $(DEPS)
