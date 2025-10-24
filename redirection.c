/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:05:25 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/22 16:53:04 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void	heredoc_sigint(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

int	redirect(char *filename, t_minishell *minishell)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		write(2, "open failed\n", 12);
		return (0);
	}
	if (minishell->oldfd_out < 0)
		minishell->oldfd_out = dup(STDOUT_FILENO);
	if (minishell->oldfd_out < 0)
	{
		close(fd);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	double_redirect(char *filename, t_minishell *minishell)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		write(2, "open failed\n", 12);
		return (0);
	}
	if (minishell->oldfd_out < 0)
		minishell->oldfd_out = dup(STDOUT_FILENO);
	if (minishell->oldfd_out < 0)
	{
		close(fd);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	redirect_left(char *filename, t_minishell *minishell)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(2, "open failed\n", 12);
		return (0);
	}
	if (minishell->oldfd_in < 0)
		minishell->oldfd_in = dup(STDIN_FILENO);
	if (minishell->oldfd_in < 0)
	{
		close(fd);
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	open_redir(char *t, int which, int *fd)
{
	if (*fd >= 0)
		close(*fd);
	if (which == '>')
	{
		if (t[1] == '>')
			*fd = open(t + 2, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			*fd = open(t + 1, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	else if (t[1] == '<')
		*fd = double_redirect_left_ultra(t + 2);
	else
		*fd = open(t + 1, O_RDONLY);
	if (*fd == -130)
		return (-130);
	if (*fd < 0)
		return (-1);
	return (1);
}
