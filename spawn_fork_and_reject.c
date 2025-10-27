/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_fork_and_reject.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:04:57 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 19:22:56 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fe_fork_error(void)
{
	perror("fork error");
	return (-1);
}

int	fe_spawn_all(t_cmds *c, int *pids)
{
	int	i;

	i = 0;
	while (c)
	{
		if (!c->argv || !c->argv[0])
		{
			fe_skip_node(&c);
			continue ;
		}
		pids[i] = fork();
		if (pids[i] == -1)
			return (fe_fork_error());
		if (pids[i] == 0)
		{
			free(pids);
			return (exec_commands(c, 0, 0, 1));
		}
		fe_close_prev(c);
		if (c->std_input > 0)
			close(c->std_input);
		c = c->next;
		i++;
	}
	return (i);
}

int	fork_and_exec_commands(t_cmds *cmds)
{
	t_cmds	*first;
	int		nb;
	int		*pids;
	int		ret;
	int		i;

	if (fe_init(cmds, &first, &nb, &ret))
		return (ret);
	pids = malloc(sizeof(int) * nb);
	if (!pids)
		return (setup_and_reset_signal(0));
	i = fe_spawn_all(first, pids);
	if (i == -1)
	{
		free(pids);
		return (setup_and_reset_signal(-1));
	}
	ret = wait_for_pids(nb, pids, -1, 0);
	free(pids);
	return (setup_and_reset_signal(ret));
}

int	reject_leading_redir_or_pipe(const char *s)
{
	int			i;
	char		tok[3];
	const char	*msg;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] != '>' && s[i] != '<' && s[i] != '|')
		return (1);
	if (s[i] == '|')
		msg = "Minishell: syntax error near unexpected token `";
	else
		msg = "Minishell: syntax error near unexcepted token `";
	tok[0] = s[i];
	tok[1] = '\0';
	if (s[i + 1] == s[i])
	{
		tok[1] = s[i];
		tok[2] = '\0';
	}
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd(tok, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

int	reject_bad_start(char *str, int *last_ret, char *line)
{
	if (str && ft_strlen(str) && !reject_leading_redir_or_pipe(str))
	{
		*last_ret = 2;
		free(line);
		return (1);
	}
	return (0);
}
