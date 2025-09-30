SRCS += $(addprefix src/exec/, \
	cmd/execute_cmd.c\
	heredoc/process_heredoc.c\
	pipe/close_parent_pipes.c\
	pipe/count_pipeline.c\
	pipe/create_pipeline.c\
	pipe/destroy_pipeline.c\
	pipe/execute_child.c\
	pipe/execute_pipe.c\
	pipe/setup_pipes.c\
	redir/exec_redirections.c\
	redir/init_redir_table.c\
	utils/find_path.c\
	execute.c\
)