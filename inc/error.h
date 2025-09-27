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

//ALLOC MESSAGE
#define ERR_MSG_ALLOC RED "Allocation failed:\t" RESET
#define ERR_MSG_ALLOC_ENV  GREEN "env.c" RESET


//FUNCTIONS
void	print_custom_error(int err);

#endif