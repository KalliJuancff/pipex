/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/03 11:41:31 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ERR_NUM_PARAMS_KO 1

#include "pipex.h"

void	ft_exit(int errcode, char *errdesc)
{
	write(STDERR_FILENO, errdesc, ft_strlen(errdesc));
	write(STDERR_FILENO, ".\n", 2);
	exit(errcode);
}

void	validate_arguments(int argc, char *argv[])
{
	if (argc != 5)
		ft_exit(ERR_NUM_PARAMS_KO, "El número de parámetros incorrecto");
}

int	main(int argc, char *argv[])
{
	validate_arguments(argc, argv);
	return (0);
}
