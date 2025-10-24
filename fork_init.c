/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:02:57 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 19:17:06 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_and_reset_signal(int ret)
{
	setup_interactive_signals();
	reset_signal_flag();
	return (ret);
}

int	fe_ret(int code, int *pret)
{
	*pret = setup_and_reset_signal(code);
	return (1);
}

int	fe_init(t_cmds *cmds, t_cmds **first, int *nb, int *pret)
{
	int	st;

	setup_parent_exec_signals();
	st = add_fd_of_heredocs(cmds);
	if (st == 130)
		return (fe_ret(130, pret));
	if (st < 0)
		return (fe_ret(1, pret));
	*first = first_executable_cmd(cmds);
	if (!*first)
		return (fe_ret(0, pret));
	*nb = count_executable_cmds(*first);
	if (*nb == 0)
		return (fe_ret(0, pret));
	if (*nb == 1 && is_built_in((*first)->argv[0]))
		return (fe_ret(exec_commands(*first, 1, 0, 1), pret));
	return (0);
}

void	fe_skip_node(t_cmds **c)
{
	if ((*c)->std_input > 0)
	{
		close((*c)->std_input);
		(*c)->std_input = 0;
	}
	*c = (*c)->next;
}

void	fe_close_prev(t_cmds *c)
{
	if (c->previous && c->previous->argv && c->previous->argv[0])
	{
		close(c->previous->fd[0]);
		close(c->previous->fd[1]);
	}
}
