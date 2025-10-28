/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:36:25 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/23 19:23:23 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_loop(int *last_ret, char ***envp_copy)
{
	char	*line;
	char	*str;

	while (1)
	{
		reset_signal_flag();
		line = readline("Minishell:");
		if (handle_eof(line))
			break ;
		if (handle_sig_and_empty(line, last_ret))
			continue ;
		str = skip_ws_ptr(line);
		if (reject_bad_start(str, last_ret, line))
			continue ;
		if (str && ft_strlen(str))
			*last_ret = process_and_run(str, envp_copy, *last_ret);
		else
			*last_ret = 0;
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		last_ret;
	char	**envp_copy;

	(void)argc;
	(void)argv;
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("minishell: not a tty\n", STDERR_FILENO);
		return (1);
	}
	last_ret = 0;
	envp_copy = copy_array_string(envp);
	if (!envp_copy)
		return (1);
	setup_interactive_signals();
	run_loop(&last_ret, &envp_copy);
	free_array(envp_copy);
	return (last_ret);
}
