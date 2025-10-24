/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   until_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:01:02 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/23 15:51:46 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_until(char *str, int *i, char c, int which)
{
	while (which == 0 && str[*i] == c)
		(*i)++;
	while (which != 0 && str[*i] && str[*i] != c)
		(*i)++;
	if (str[*i] == c && which == 1)
		(*i)++;
}

void	get_arg_or_redir(char *str, int *i, int is_arg, int *nb_of_x)
{
	skip_until(str, i, ' ', 0);
	if (str[*i] == '\"')
	{
		skip_until(str, i, '\"', 1);
		if (!is_arg)
			(*nb_of_x) += 1;
	}
	else if (str[*i] == '\'')
	{
		skip_until(str, i, '\'', 1);
		if (!is_arg)
			(*nb_of_x) += 1;
	}
	else
	{
		while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '\"'
			&& str[*i] != '>' && str[*i] != '<')
			(*i)++;
		if (!is_arg)
			(*nb_of_x) += 1;
	}
}

void	nbp_handle_quote(char *s, int *i, int *n, int is_arg)
{
	if (s[*i] == '\'')
		skip_until(s, i, '\'', 1);
	else
		skip_until(s, i, '\"', 1);
	if (is_arg)
		(*n)++;
}

int	nbp_skip_word(char *s, int i)
{
	while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"'
		&& s[i] != '>' && s[i] != '<')
		i++;
	return (i);
}

int	nb_x_until_pipe(char *s, int i, int is_arg)
{
	int	n;

	n = 0;
	while (s[i] && s[i] != '|')
	{
		skip_until(s, &i, ' ', 0);
		if (s[i] == '\'' || s[i] == '\"')
			nbp_handle_quote(s, &i, &n, is_arg);
		else if (s[i] == '<' || s[i] == '>')
		{
			i++;
			if (s[i] == s[i - 1])
				i++;
			get_arg_or_redir(s, &i, is_arg, &n);
		}
		else if (s[i] && s[i] != '|')
		{
			i = nbp_skip_word(s, i);
			if (is_arg)
				n++;
		}
	}
	return (n);
}
