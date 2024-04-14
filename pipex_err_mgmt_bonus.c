/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_err_mgmt_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:23:27 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/14 15:50:39 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_with_internal_error(void)
{
	perror(NULL);
	exit(ERR_INTERNAL_ERROR);
}

void	exit_with_custom_error(int err_code, char *err_msg)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", 1);
	exit(err_code);
}
