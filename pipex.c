/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/03 15:51:55 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_arguments(int argc, char *argv[])
{
	if (argc != 5)
		ft_exit(ERR_NUM_PARAMS_KO, "Número de parámetros incorrecto");
}

t_prgdata	*create_program_data(int argc, char *argv[])
{
	t_prgdata	*ret;

	ret = (t_prgdata *) malloc(1 * sizeof(t_prgdata));
	ret->infile = ft_strdup(argv[1]);
	ret->outfile = ft_strdup(argv[argc - 1]);
	ret->cmddata = (t_cmddata *) malloc(2 * sizeof(t_cmddata));
	ret->cmddata[0].cmdname = ft_strdup(argv[2]);
	ret->cmddata[1].cmdname = ft_strdup(argv[3]);
	return (ret);
}

void	release_program_data(t_prgdata *data)
{
	free(data->infile);
	free(data->cmddata[0].cmdname);
	free(data->cmddata[1].cmdname);
	free(data->cmddata);
	free(data->outfile);
	free(data);
}

int	main(int argc, char *argv[])
{
	t_prgdata	*data;

	validate_arguments(argc, argv);
	data = create_program_data(argc, argv);
	printf(" Infile: %s\n", data->infile);
	printf("Cmd. #1: %s\n", data->cmddata[0].cmdname);
	printf("Cmd. #2: %s\n", data->cmddata[1].cmdname);
	printf("Outfile: %s\n", data->outfile);
	release_program_data(data);
	return (0);
}
