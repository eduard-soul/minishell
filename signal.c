/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:32:26 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/29 16:34:00 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

static volatile sig_atomic_t	g_sig = 0;

void	set_flag(int value)
{
	if (value)
		g_sig |= (1 << 0);
	else
		g_sig &= ~(1 << 0);
}

int	get_signal_flag(void)
{
	return ((g_sig & (1 << 0)) != 0);
}

void	set_mode(int mode)
{
	g_sig &= ~0b1110;
	g_sig |= mode;
}

int	get_sig_mode(void)
{
	return (g_sig & 0b1110);
}

void	sig_handler(int signum, siginfo_t *siginfo, void *sigclient)
{
	(void)siginfo;
	(void)sigclient;
	if (signum == SIGINT && get_sig_mode() == (0 << 1))
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		set_flag(1);
	}
}
