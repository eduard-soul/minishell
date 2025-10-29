/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_close_dup_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 01:09:37 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/29 01:09:37 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_empty_argv(t_cmds *cmds, int is_alone_builtin)
{
	check_and_close_fds(cmds);
	if (is_alone_builtin)
		return (0);
	safe_exit_with_cmds(cmds, 0);
	return (0);
}

int	handle_stdin_dup(t_cmds *cmds)
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
	}
	return (2);
}
