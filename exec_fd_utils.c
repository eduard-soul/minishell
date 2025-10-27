/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:25:04 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 19:14:14 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_and_save_dup(t_cmds *cmds, int save_fd_in_out[2],
			int is_alone_builtin, int *is_child)
{
	if (is_alone_builtin)
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
	}
	if (!cmds->argv || !cmds->argv[0])
	{
		check_and_close_fds(cmds);
		if (is_alone_builtin)
			return (0);
		safe_exit_with_cmds(cmds, 0);
	}
	if ((cmds->previous && !cmds->std_input
			&& dup2(cmds->previous->fd[0], STDIN_FILENO) == -1)
		|| ((cmds->std_input > 0 && dup2(cmds->std_input, STDIN_FILENO) == -1)))
	{
		perror("dup2");
		safe_exit_with_cmds(cmds, 1);
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

int	get_fd_and_process(t_cmds *cmds, int is_alone_builtin,
			int save_fd_in, int save_fd_out)
{
	int	fd;

	fd = end_to_redirections(cmds->redirections, '>');
	if (fd < 0)
	{
		check_and_close_fds(cmds);
		if (is_alone_builtin)
			dup_and_close(save_fd_in, save_fd_out);
		if (is_alone_builtin)
			return ((fd == -2) + 1);
		safe_exit_with_cmds(cmds, (fd == -2) + 1);
	}
	if (fd > 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror_and_exit("dup2", 1);
		close(fd);
	}
	if (cmds->next && fd < 1 && (dup2(cmds->fd[1], STDOUT_FILENO) == -1))
		perror_and_exit("dup2", 1);
	if (!is_built_in(cmds->argv[0]))
		check_and_close_fds(cmds);
	return (0);
}

int	exec_builtin_and_close_fds(t_cmds *cmds, int is_child, int is_alone_builtin,
							int save_fd_in_out[2])
{
	int	ret;

	ret = exec_builtin_impl(cmds->argv, STDOUT_FILENO, cmds->envp, is_child, cmds);
	check_and_close_fds(cmds);
	if (is_alone_builtin)
		dup_and_close(save_fd_in_out[0], save_fd_in_out[1]);
	if (is_alone_builtin)
		return (ret);
	safe_exit_with_cmds(cmds, ret);
	return (0);
}

int	exec_commands(t_cmds *cmds, int is_alone_builtin, int ret, int is_child)
{
	int		save_fd_in_out[2];

	if (!is_alone_builtin)
		setup_child_signals();
	ret = check_and_save_dup(cmds, save_fd_in_out,
			is_alone_builtin, &is_child);
	if (ret != 2)
		return (ret);
	ret = get_fd_and_process(cmds, is_alone_builtin, save_fd_in_out[0],
			save_fd_in_out[1]);
	if (ret)
		return (ret);
	if (is_built_in(cmds->argv[0]))
		return (exec_builtin_and_close_fds(cmds, is_child, is_alone_builtin,
				save_fd_in_out));
	else if (ft_search_char_in_str(cmds->argv[0], '/'))
		exec_absolute_path(cmds);
	else
		search_path_and_exec(cmds);
	safe_exit_with_cmds(cmds, 1);
	return (0);
}
