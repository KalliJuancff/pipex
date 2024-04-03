/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:27:15 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/03 18:09:01 by jfidalgo         ###   ########.fr       */
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

# define ERR_NUM_PARAMS_KO 1
# define ERR_MALLOC_FAILED 2

struct	s_cmddata
{
	char	*cmdname;
	char	**options;
};
typedef struct s_cmddata	t_cmddata;

struct	s_prgdata
{
	char		*infile;
	char		*outfile;
	t_cmddata	**cmddata;
};
typedef struct s_prgdata	t_prgdata;

void	ft_exit(int errcode);
void	ft_exit2(int errcode, char *errdesc);

#endif
