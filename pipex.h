/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:27:15 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/03 12:21:38 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

	// perror
# include <stdio.h>
	// exit, wait
# include <stdlib.h>
	// STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, ...
	// ... close, fork, getpid, pid_t, read, write
# include <unistd.h>

# include "libft/libft.h"

#define ERR_NUM_PARAMS_KO 1

void	ft_exit(int errcode, char *errdesc);

#endif
