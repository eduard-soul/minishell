/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:45:45 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 15:47:18 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_name_delim(char c)
{
	if (c == 0)
		return (1);
	if (c == ' ' || c == '\'' || c == '\"' || c == '>'
		|| c == '<' || c == '|')
		return (1);
	return (0);
}

void	skip_quoted_block(char *s, int *i)
{
	char	q;

	q = s[(*i)++];
	while (s[*i] && s[*i] != q)
		(*i)++;
	if (s[*i] == q)
		(*i)++;
}

void	skip_to_word_end(char *s, int *i)
{
	while (s[*i] && !is_name_delim(s[*i]))
		(*i)++;
}

int	len_quoted(char *s, int p)
{
	int		n;
	char	q;

	n = 0;
	q = s[p++];
	while (s[p] && s[p] != q)
	{
		n++;
		p++;
	}
	return (n);
}

int	len_word(char *s, int p)
{
	int	n;

	n = 0;
	while (s[p] && !is_name_delim(s[p]))
	{
		n++;
		p++;
	}
	return (n);
}
