/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:33 by jureix-c          #+#    #+#             */
/*   Updated: 2025/03/20 18:02:33 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODES_H
# define NODES_H

// INCLUDES
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>

// DEFINES
# define VALUE_UNSET -1
# define VALUE_FROM_ARG -2

// STRUCTURES
// Content type per node, self explanatory
typedef enum e_printf_nodes_type
{
	NODE_TYPE_CHAR, // %c
	NODE_TYPE_STRING, // %s
	NODE_TYPE_POINTER, // %p
	NODE_TYPE_INTEGER, // %i %d
	NODE_TYPE_UNSIGNED, // %u
	NODE_TYPE_HEX_LOWER, // %x
	NODE_TYPE_HEX_UPPER, // %X
	NODE_TYPE_WRITTEN_COUNT, // %n
	NODE_TYPE_PERCENT, // %%
	NODE_TYPE_TEXT, // Node containing plain text
}	t_printf_nodes_type;

// Union to allow different argument's types in struct
typedef union u_printf_node_data
{
	char				c;
	const char			*s;
	void				*p;
	int					d;
	unsigned int		u;
	long				ld;
	long long			lld;
	unsigned long		lu;
	unsigned long long	llu;
}	t_printf_node_data;

// Simple linked list nodes
typedef struct s_printf_node
{
	// Base values
	struct s_printf_node	*next;
	t_printf_nodes_type		type;
	// Content
	t_printf_node_data		data;
	int						string_len;
	// Generic modifiers
	int						flag_minus; // Left-justify with given width
	int						flag_zero; // Pad with zeros
	int						flag_plus; // Prefix '+' for positive numbers
	int						flag_space; // Prefix for positive numbers
	int						flag_hash; // Alternative form
	// Type modifiers
	int						flag_h; // Expect short or char
	int						flag_l; // Expect long or long long
	int						flag_bigl; // Expect long double
	int						flag_j; // Expect intmax_t or uintmax_t
	int						flag_z; // Expect size_t
	int						flag_t; // Expect ptrdiff_t
	// Width and precision
	int						width; // Min width of the output
	int						precision; // Decimal precision
}	t_printf_node;

// CIRCULAR INCLUDES FIX
typedef struct s_printf_data	t_printf_data;
typedef struct s_printf_output	t_printf_output;

// LEXER FUNCTIONS PROTOTYPES
int				lex_nodes(t_printf_data *data, va_list av);
int				lex_node(const char *f, va_list av, t_printf_node *node);
int				lex_node_params(const char *f, va_list av, t_printf_node *node);
int				lex_node_flags(const char *f, t_printf_node *node);
void			lex_node_flag(const char match, t_printf_node *node);
int				lex_node_widths(const char *f, t_printf_node *node);
int				lex_node_type(const char *f, va_list av, t_printf_node *node);

// NODES INIT PROTOTYPES
void			init_char_node(va_list av, t_printf_node *node);
void			init_string_node(va_list av, t_printf_node *node);
void			init_pointer_node(va_list av, t_printf_node *node);
void			init_int_node(va_list av, t_printf_node *node, \
					bool is_unsigned);
void			init_hex_node(va_list av, t_printf_node *node, bool is_upper);
void			init_written_count_node(va_list av, t_printf_node *node);
void			init_percent_node(va_list av, t_printf_node *node);
void			init_text_node(const char *f, t_printf_node *node);

// NODES DUMP PROTOTYPES
int				dump_nodes(t_printf_data *data);
int				dump_node(t_printf_output *out, t_printf_node *node);
int				dump_char_node(t_printf_output *out, t_printf_node *node);
int				dump_string_node(t_printf_output *out, t_printf_node *node);
int				dump_pointer_node(t_printf_output *out, t_printf_node *node);
int				dump_int_node(t_printf_output *out, t_printf_node *node);
int				dump_hex_node(t_printf_output *out, t_printf_node *node);
int				dump_written_count_node(t_printf_output *out, \
					t_printf_node *node);
int				dump_percent_node(t_printf_output *out);
int				dump_text_node(t_printf_output *out, t_printf_node *node);

// NODES LEN PROTOTYPES
int				get_nodes_total_len(t_printf_node *nodes);
int				get_node_len(t_printf_node *node);
int				get_char_node_len(t_printf_node *node);
int				get_string_node_len(t_printf_node *node);
int				get_pointer_node_len(t_printf_node *node);
int				get_int_node_len(t_printf_node *node);
int				get_hex_node_len(t_printf_node *node);
int				get_percent_node_len(t_printf_node *node);
int				get_text_node_len(t_printf_node *node);

// NODES HELPERS PROTOTYPES
uint64_t		get_int_node_raw_value(t_printf_node *node);
char			get_int_node_sign(t_printf_node *node);
void			get_int_node_lens(t_printf_node *node, int *raw_len, int *len);
int				dump_int_lpad(t_printf_output *out, t_printf_node *node, \
					int p_len, char s);
void			get_hex_node_lens(t_printf_node *node, int *raw_len, int *len);
int				dump_hex_prefix(t_printf_output *out, t_printf_node *node);
int				dump_hex_lpad(t_printf_output *out, t_printf_node *node, \
					int p_len);

// NODES FUNCTIONS PROTOTYPES
t_printf_node	*printf_node_new(void);
void			printf_node_add_back(t_printf_node *nodes, t_printf_node *node);
void			printf_nodes_clean(t_printf_node *nodes);
void			printf_node_extract_flags(va_list av, t_printf_node *node);
t_printf_node	*printf_node_last(t_printf_node *nodes);

#endif
