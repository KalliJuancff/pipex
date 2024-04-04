/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:48 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/04 12:55:00 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_program_data(t_prgdata data)
{
	int	i;

	printf(" Infile: %s\n", data.infile);
	i = 0;
	while (data.commands[i] != NULL)
	{
		printf("Cmd. #%d: %s\n", i + 1, data.commands[i]);
		i++;
	}
	printf("Outfile: %s\n", data.outfile);
}

int	main(int argc, char *argv[])
{
	t_prgdata	data;

	validate_arguments(argc, argv);
	initialize_program_data(&data, argc, argv);
	show_program_data(data);
	release_program_data(data);
	return (0);
}
