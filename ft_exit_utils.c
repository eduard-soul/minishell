/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:02:02 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/28 13:02:30 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric_argument(char *str)
{
	int	index;

	if (!str || !str[0])
		return (0);
	index = 0;
	if (str[index] == '+' || str[index] == '-')
		index++;
	if (!str[index])
		return (0);
	while (str[index])
	{
		if (str[index] < '0' || str[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

int	parse_exit_val(char *str, long long *value)
{
	int					sign;
	unsigned long long	number;
	unsigned long long	limit;

	sign = 1;
	number = 0;
	limit = (unsigned long long)LLONG_MAX;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		number = number * 10 + (*str - '0');
		if ((sign == 1 && number > limit)
			|| (sign == -1 && number > limit + 1))
			return (0);
		str++;
	}
	*value = (long long)number;
	if (sign == -1)
		*value = -(long long)number;
	return (1);
}

int	argument_count(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}

int	normalize_code(long long number)
{
	int	code;

	code = (int)(number % 256);
	if (code < 0)
		code += 256;
	return (code);
}

void	put_err_for_exit(t_cmds *cmds, char **argv, int code)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argv[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	safe_exit_with_cmds(cmds, code);
}
