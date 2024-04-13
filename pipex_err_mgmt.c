/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:03:01 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/10 10:20:05 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_with_internal_error(void)
{
	perror(NULL);
	exit(errno);
}

void	exit_with_custom_error(int err_code, char *err_msg)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
	exit(err_code);
}
