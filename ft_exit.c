/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:02:31 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/23 15:08:34 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_argument(char *str)
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

static int	parse_exit_val(char *str, long long *value)
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

static int	argument_count(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}

static int	normalize_code(long long number)
{
	int	code;

	code = (int)(number % 256);
	if (code < 0)
		code += 256;
	return (code);
}

int	ft_exit(char **argv, int is_child)
{
	int			argc;
	long long	exit_value;
	int			code;

	argc = argument_count(argv);
	if (!is_child)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argc <= 1)
		exit(0);
	if (!is_numeric_argument(argv[1]) || !parse_exit_val(argv[1], &exit_value))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		if (is_child)
			exit(1);
		return (1);
	}
	code = normalize_code(exit_value);
	exit(code);
}
