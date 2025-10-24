/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:12:38 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/22 16:33:36 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_option(char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	if (!s[i])
		return (0);
	while (s[i] == 'n')
		i++;
	if (s[i] != '\0')
		return (0);
	return (1);
}

int	ft_echo_ultra(char **argv, int fd)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	while (argv[i] && is_n_option(argv[i]))
	{
		no_newline = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd);
		if (argv[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!no_newline)
		ft_putstr_fd("\n", fd);
	return (0);
}

/*
void	ft_echo(t_minishell *minishell)
{
	int	no_option_n;
	int	i;

	no_option_n = 1;
	while (minishell->args[0] && minishell->args[0] == ' ')
	// maybe all type of spaces 
		minishell->args++;
	if (minishell->args[0] && minishell->args[0] == '-' &&
		minishell->args[1]&& minishell->args[1] == 'n' && 
		(!minishell->args[2] || minishell->args[2] == ' '))
		// maybe all type of spaces
	{
		no_option_n = 0;
		if (minishell->args[2])
			minishell->args += 2;
		else
			minishell->args += 3;
	}
	while (minishell->args[0] && minishell->args[0] == ' ')
	// maybe all type of spaces 
		minishell->args++;
	i = ft_strlen(minishell->args);
	minishell->output_cmd = 
	malloc(sizeof(char) * (i + no_option_n + 1));
	if (!minishell->output_cmd) // prob de malloc = ret 2 ??
	{
		minishell->last_ret = 2;	
		write(2, "echo malloc error\n", 18);
		return ;
	}
	minishell->output_cmd[i + no_option_n] = '\0';
	if (no_option_n)
		minishell->output_cmd[i] = '\n';
	while (i)
	{
		minishell->output_cmd[i - 1] = minishell->args[i - 1];
		i--;
	}
	minishell->last_ret = 0;
	return ;
}
*/
/*
char *ft_echo(t_minishell *minishell)
{
	int		i;
	int		len;
	char	*dup;
	int 	option_n; // temporary just for tests;
		//sans option n abc
		//abc\n

		//len = 3 + 1 bn = 4
		//malloc = 4 + 1 \0 = 5	
	len = 0;
	while (!is_unexepexcted_ecected_van_dyhk((minishell->str)[len]))
		len++;
	if (option_n == 0)
		len += 1;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len - !option_n)
	{
		dup[i] = (minishell->str)[i];
		i++;
	}
	if (option_n == 0)
		dup[i++] = '\n';
	dup[i] = '\0';
	return (dup); 
}
*/
