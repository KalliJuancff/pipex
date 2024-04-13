/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_err_mgmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:03:01 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/13 22:47:01 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_with_internal_error(void)
{
	perror(NULL);
	exit(1);
}

void	exit_with_custom_error(int err_code, char *err_msg)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
	exit(err_code);
}
