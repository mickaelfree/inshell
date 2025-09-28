SRCS += $(addprefix src/parsing/, \
	expand/expand_env.c\
	expand/expand_quoted.c\
	expand/expand_sizer.c\
	expand/expand_utils.c\
	pipe/build_pipeline.c\
	redir/redirection_handler.c\
	redir/redirection_utils.c\
	token/process_token.c\
	token/can_token.c\
	token/handle_token.c\
	token/identify_token.c\
	token/quote_handler.c\
	token/token_utils.c\
	parsing.c\
)
