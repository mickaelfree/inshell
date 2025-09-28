SRCS += $(addprefix src/builtins/, \
	cd/cd.c\
	echo/echo.c\
	env/env.c\
	env/init_env.c\
	exit/exit.c\
	export/export.c\
	pwd/pwd.c\
	unset/unset.c\
	utils/builtin_utils.c\
	utils/is_builtin.c\
	execute_builtin.c\
)