/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:30 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/28 02:51:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// COLORS
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define CYAN "\033[36m"
# define RESET "\e[0m"

// BASIC MESSAGE
# define ERR_MESSAGE "ERROR :\t"

// ALLOC CODES
# define ERR_ALLOC_ENV 4201
# define ERR_ALLOC_EXPORT 4202
# define ERR_ALLOC_UNSET 4203
# define ERR_ALLOC_PIPE_BUILD 4204
# define ERR_ALLOC_PIPE_UTILS 4205

// ALLOC MESSAGE
# define ERR_MSG_ALLOC "Allocation failed:\t"
# define ERR_MSG_ALLOC_ENV "env.c"
# define ERR_MSG_ALLOC_EXPORT "export.c"
# define ERR_MSG_ALLOC_UNSET "unset.c"
# define ERR_MSG_ALLOC_PIPE_BUILD "build_pipeline.c"
# define ERR_MSG_ALLOC_PIPE_UTILS "pipeline_utils.c"

// FUNCTIONS
void	print_custom_error(int err);
int		print_error_ret_err(int err);
void	*print_error_ret_null(int err);

#endif