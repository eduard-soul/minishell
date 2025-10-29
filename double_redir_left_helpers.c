/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redir_left_helpers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:28:41 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 19:46:30 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fds(t_cmds *cmds)
{
	t_cmds	*tmp;

	tmp = cmds;
	while (tmp->previous)
		tmp = tmp->previous;
	while (tmp)
	{
		if (tmp->fd[0] > 2)
			close(tmp->fd[0]);
		if (tmp->fd[1] > 2)
			close(tmp->fd[1]);
		tmp = tmp->next;
	}
}

void	process_heredoc_line(int wfd, char *line, t_cmds *cmds)
{
	if (write(wfd, line, ft_strlen(line)) != ft_strlen(line)
		|| write(wfd, "\n", 1) != 1)
	{
		free(line);
		close(wfd);
		safe_exit_with_cmds(cmds, 1);
	}
	free(line);
}

void	hd_child(int wfd, char *delim, t_cmds *cmds)
{
	char	*line;

	close_all_fds(cmds);
	hd_setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		process_heredoc_line(wfd, line, cmds);
	}
	close(wfd);
	safe_exit_with_cmds(cmds, 0);
}
