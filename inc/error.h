#ifndef ERROR_H
#define ERROR_H

//COLORS
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define CYAN "\033[36m"
# define RESET "\e[0m"

//BASIC MESSAGE
# define ERR_MESSAGE "ERROR :\t"

//ALLOC CODES
#define ERR_ALLOC_ENV 4201
#define ERR_ALLOC_EXPORT 4202

//ALLOC MESSAGE
#define ERR_MSG_ALLOC RED "Allocation failed:\t" RESET
#define ERR_MSG_ALLOC_ENV  GREEN "env.c" RESET
#define ERR_MSG_ALLOC_EXPORT  GREEN "export.c" RESET


//FUNCTIONS
void	print_custom_error(int err);
int		print_error_and_ret(int err);

#endif