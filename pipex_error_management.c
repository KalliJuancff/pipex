/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:03:01 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/07 18:53:15 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(int errcode)
{
	int	errcode2;

	if (errcode == ERR_NUM_PARAMS_KO)
		ft_exit2(errcode, "Número de parámetros incorrecto");
	// TODO: Pensarme si lo quiero hacer así (poder especificar cualquier número como código de error)
	write(STDERR_FILENO, "Error: ", 7);
	// TODO: De mantenerlo, actualizar estas líneas para usar ft_itoa
	errcode2 = errcode + '0';
	write(STDERR_FILENO, &errcode2, 1);
	write(STDERR_FILENO, "\n", 1);
}

void	ft_exit2(int errcode, char *errdesc)
{
	write(STDERR_FILENO, errdesc, ft_strlen(errdesc));
	write(STDERR_FILENO, ".\n", 2);
	exit(errcode);
}
