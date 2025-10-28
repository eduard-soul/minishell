/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirection_left.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:28:41 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 16:16:54 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hd_setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = heredoc_sigint;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("sigaction");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}

void	hd_child(int wfd, char *delim, t_cmds *cmds)
{
	char		*line;

	hd_setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		if (write(wfd, line, ft_strlen(line)) != ft_strlen(line)
			|| write(wfd, "\n", 1) != 1)
		{
			free(line);
			close(wfd);
			safe_exit_with_cmds(cmds, 1);
		}
		free(line);
	}
	close(wfd);
	safe_exit_with_cmds(cmds, 0);
}

int	hd_parent_wait(int rfd, pid_t pid)
{
	int	status;

	setup_parent_exec_signals();
	waitpid(pid, &status, 0);
	setup_interactive_signals();
	reset_signal_flag();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(rfd);
		return (-130);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(rfd);
		return (-1);
	}
	return (rfd);
}

int	double_redirect_left_ultra(char *delimiter, t_cmds *cmds)
{
	pid_t	pid;
	int		fd[2];

	if (!delimiter)
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		hd_child(fd[1], delimiter, cmds);
	}
	close(fd[1]);
	return (hd_parent_wait(fd[0], pid));
}
