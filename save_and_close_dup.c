/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_and_close_dup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:49:16 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 19:37:41 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_stdio_if_alone(int save_fd_in_out[2], int *is_child)
{
	*is_child = 0;
	save_fd_in_out[0] = dup(STDIN_FILENO);
	save_fd_in_out[1] = dup(STDOUT_FILENO);
	if (save_fd_in_out[0] == -1 || save_fd_in_out[1] == -1)
	{
		perror("dup");
		if (save_fd_in_out[0] != -1)
			close(save_fd_in_out[0]);
		if (save_fd_in_out[1] != -1)
			close(save_fd_in_out[1]);
		return (1);
	}
	return (0);
}

void	apply_stdin_from_cmd(t_cmds *cmds)
{
	if (cmds->std_input > 0)
	{
		if (dup2(cmds->std_input, STDIN_FILENO) == -1)
		{
			perror("dup2");
			safe_exit_with_cmds(cmds, 1);
		}
		close(cmds->std_input);
		cmds->std_input = 0;
	}
	else if (cmds->previous)
	{
		if (dup2(cmds->previous->fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			safe_exit_with_cmds(cmds, 1);
		}
		close(cmds->previous->fd[0]);
	}
}

int	check_and_save_dup(t_cmds *cmds, int save_fd_in_out[2],
			int is_alone_builtin, int *is_child)
{
	if (is_alone_builtin)
	{
		if (save_stdio_if_alone(save_fd_in_out, is_child))
			return (1);
	}
	if (!cmds->argv || !cmds->argv[0])
	{
		check_and_close_fds(cmds);
		if (is_alone_builtin)
			return (0);
		safe_exit_with_cmds(cmds, 0);
	}
	if (cmds->std_input > 0)
	{
		if (dup2(cmds->std_input, STDIN_FILENO) == -1)
		{
			perror("dup2");
			safe_exit_with_cmds(cmds, 1);
		}
		close(cmds->std_input);
		cmds->std_input = 0;
	}
	else if (cmds->previous)
	{
		if (dup2(cmds->previous->fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			safe_exit_with_cmds(cmds, 1);
		}
	}
	return (2);
}

void	dup_and_close(int save_fd_in, int save_fd_out)
{
	dup2(save_fd_in, STDIN_FILENO);
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
	close(save_fd_in);
}
