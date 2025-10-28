/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:02:31 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/28 13:03:58 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **argv, int is_child, t_cmds *cmds)
{
	int			argc;
	long long	exit_value;
	int			code;

	argc = argument_count(argv);
	if (!is_child)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argc <= 1)
		safe_exit_with_cmds(cmds, 0);
	if (!is_numeric_argument(argv[1]) || !parse_exit_val(argv[1], &exit_value))
		put_err_for_exit(cmds, argv, 2);
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		if (is_child)
			safe_exit_with_cmds(cmds, 1);
		return (1);
	}
	code = normalize_code(exit_value);
	safe_exit_with_cmds(cmds, code);
	return (0);
}
