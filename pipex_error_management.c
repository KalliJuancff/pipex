/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:03:01 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/04 11:29:58 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(int errcode)
{
	if (errcode == ERR_NUM_PARAMS_KO)
		ft_exit2(errcode, "Número de parámetros incorrecto");
}

void	ft_exit2(int errcode, char *errdesc)
{
	write(STDERR_FILENO, errdesc, ft_strlen(errdesc));
	write(STDERR_FILENO, ".\n", 2);
	exit(errcode);
}
