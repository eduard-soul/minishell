/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:32:26 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/22 17:04:24 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

static volatile t_sigstate	g_sigstate = {0, SIGM_INTERACTIVE};

void	set_flag(sig_atomic_t value)
{
	if (value)
		g_sigstate.flag = 1;
	else
		g_sigstate.flag = 0;
}

void	set_mode(sig_atomic_t mode)
{
	g_sigstate.mode = mode;
}

void	sig_handler(int signum, siginfo_t *siginfo, void *sigclient)
{
	(void)siginfo;
	(void)sigclient;
	if (signum == SIGINT && g_sigstate.mode == SIGM_INTERACTIVE)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		set_flag(1);
	}
}

void	signal_managment(int signum, siginfo_t *siginfo, void *sigclient)
{
	sig_handler(signum, siginfo, sigclient);
}

int	get_signal_flag(void)
{
	return ((int)g_sigstate.flag);
}
