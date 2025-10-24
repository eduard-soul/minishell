/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:26:07 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 18:28:07 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_pids(int nb_cmds, int *pids, int i, int exit_code)
{
	int		status;
	pid_t	pid;

	while (++i < nb_cmds)
	{
		pid = waitpid(pids[i], &status, 0);
		if (pid == -1)
		{
			if (errno == EINTR)
				continue ;
			perror("waitpid");
			return (-1);
		}
		if (pid == pids[nb_cmds - 1] && WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (pid == pids[nb_cmds - 1] && WIFSIGNALED(status))
		{
			exit_code = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		}
	}
	return (exit_code);
}

int	add_fd_of_heredocs(t_cmds *cmds)
{
	t_cmds	*copy;
	int		status;

	copy = cmds;
	while (copy)
	{
		status = end_to_redirections(copy->redirections, '<');
		if (status == -130)
			return (130);
		if (status < 0)
			return (-1);
		copy->std_input = status;
		copy = copy->next;
	}
	return (0);
}
