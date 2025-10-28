/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:25:04 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 20:32:33 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd_and_process(t_cmds *cmds, int is_alone_builtin,
			int save_fd_in, int save_fd_out)
{
	int	fd;

	fd = end_to_redirections(cmds->redirections, '>', NULL);
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

	if (is_alone_builtin && cmds->argv && cmds->argv[0]
		&& ft_strcmp(cmds->argv[0], "exit") == 0)
	{
		check_and_close_fds(cmds);
		dup_and_close(save_fd_in_out[0], save_fd_in_out[1]);
		return (exec_builtin_impl(cmds->argv, STDOUT_FILENO, is_child, cmds));
	}
	ret = exec_builtin_impl(cmds->argv, STDOUT_FILENO, is_child, cmds);
	check_and_close_fds(cmds);
	if (is_alone_builtin)
		dup_and_close(save_fd_in_out[0], save_fd_in_out[1]);
	if (is_alone_builtin)
		return (ret);
	safe_exit_with_cmds(cmds, ret);
	return (0);
}

void	close_all_other_heredoc_fds(t_cmds *cmds, t_cmds *current)
{
	t_cmds	*tmp;

	tmp = cmds;
	while (tmp->previous)
		tmp = tmp->previous;
	while (tmp)
	{
		if (tmp != current && tmp->std_input > 0)
		{
			close(tmp->std_input);
			tmp->std_input = 0;
		}
		tmp = tmp->next;
	}
}

void	close_other_heredocs(t_cmds *cmds)
{
	t_cmds	*first;

	first = cmds;
	while (first->previous)
		first = first->previous;
	close_all_other_heredoc_fds(first, cmds);
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
	if (!is_alone_builtin)
		close_other_heredocs(cmds);
	ret = get_fd_and_process(cmds, is_alone_builtin, save_fd_in_out[0],
			save_fd_in_out[1]);
	if (ret)
		return (ret);
	if (is_built_in(cmds->argv[0]))
		return (exec_builtin_and_close_fds(cmds, is_child, is_alone_builtin,
				save_fd_in_out));
	if (ft_search_char_in_str(cmds->argv[0], '/'))
		exec_absolute_path(cmds);
	else
		search_path_and_exec(cmds);
	safe_exit_with_cmds(cmds, 1);
	return (0);
}
