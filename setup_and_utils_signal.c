/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_and_utils_signal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:58:59 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/29 16:35:04 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_signal_flag(void)
{
	set_flag(0);
}

void	install_sigint_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("sigaction");
}

void	setup_interactive_signals(void)
{
	set_mode((0 << 1));
	install_sigint_handler();
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}

void	setup_parent_exec_signals(void)
{
	set_mode(1 << 1);
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("signal");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}

void	setup_child_signals(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		perror("signal");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("signal");
}
