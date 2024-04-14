/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redir_cmds_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:25:08 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/04/14 12:25:10 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	redirect_first_command(t_prgdata dt, int pipefd[2])
{
	int	flags;
	int	filefd;

	flags = O_RDONLY;
	filefd = open(dt.infile, flags);
	if (filefd == -1)
		exit_with_internal_error();
	if (dup2(filefd, STDIN_FILENO) == -1)
		exit_with_internal_error();
	if (close(filefd) == -1)
		exit_with_internal_error();
	if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1)
		exit_with_internal_error();
	if (close(pipefd[WRITE_END]) == -1)
		exit_with_internal_error();
	if (close(pipefd[READ_END]) == -1)
		exit_with_internal_error();
}

void	redirect_last_command(t_prgdata dt, int prev_read_fd)
{
	int		flags;
	mode_t	mode;
	int		filefd;

	if (dup2(prev_read_fd, STDIN_FILENO) == -1)
		exit_with_internal_error();
	if (close(prev_read_fd) == -1)
		exit_with_internal_error();
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	mode = (S_IRUSR | S_IWUSR) | S_IRGRP | S_IROTH;
	filefd = open(dt.outfile, flags, mode);
	if (filefd == -1)
		exit_with_internal_error();
	if (dup2(filefd, STDOUT_FILENO) == -1)
		exit_with_internal_error();
	if (close(filefd) == -1)
		exit_with_internal_error();
}

void	redirect_middle_command(int pipefd[2], int prev_read_fd)
{
	if (dup2(prev_read_fd, STDIN_FILENO) == -1)
		exit_with_internal_error();
	if (close(prev_read_fd) == -1)
		exit_with_internal_error();
	if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1)
		exit_with_internal_error();
	if (close(pipefd[WRITE_END]) == -1)
		exit_with_internal_error();
	if (close(pipefd[READ_END]) == -1)
		exit_with_internal_error();
}
