/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:06:22 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 20:10:20 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_ws_ptr(char *s)
{
	if (!s)
		return (s);
	while (*s == ' ')
		s++;
	return (s);
}

int	handle_sig_and_empty(char *line, int *last_ret)
{
	if (get_signal_flag())
	{
		*last_ret = 130;
		reset_signal_flag();
		if (!line[0])
		{
			free(line);
			return (1);
		}
	}
	return (0);
}

int	handle_eof(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}
