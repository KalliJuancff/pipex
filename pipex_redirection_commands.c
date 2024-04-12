/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redirection_commands.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:39:35 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/12 17:39:37 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_first_command(t_prgdata dt, int pipefd[2])
{
	int	flags;
	int	filefd;

	flags = O_RDONLY;
	filefd = open(dt.infile, flags);
	dup2(filefd, STDIN_FILENO);
	close(filefd);
	dup2(pipefd[WRITE_END], STDOUT_FILENO);
	close(pipefd[WRITE_END]);
	close(pipefd[READ_END]);
}

void	redirect_last_command(t_prgdata dt, int prev_read_fd)
{
	int		flags;
	mode_t	mode;
	int		filefd;

	dup2(prev_read_fd, STDIN_FILENO);
	close(prev_read_fd);
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	mode = (S_IRUSR | S_IWUSR) | S_IRGRP | S_IROTH;
	filefd = open(dt.outfile, flags, mode);
	dup2(filefd, STDOUT_FILENO);
	close(filefd);
}

void	redirect_middle_command(int prev_read_fd, int pipefd[2])
{
	dup2(prev_read_fd, STDIN_FILENO);
	close(prev_read_fd);
	dup2(pipefd[WRITE_END], STDOUT_FILENO);
	close(pipefd[WRITE_END]);
	close(pipefd[READ_END]);
}
