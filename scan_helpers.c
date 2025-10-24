/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:46:28 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/23 15:52:19 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta(char c)
{
	if (c == '\0' || c == ' ' || c == '\t'
		|| c == '\'' || c == '\"'
		|| c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	token_len(char *s, int i)
{
	int		len;
	char	q;

	len = 0;
	if (s[i] == '\'' || s[i] == '\"')
	{
		q = s[i++];
		while (s[i] && s[i] != q)
		{
			len++;
			i++;
		}
		return (len);
	}
	while (s[i] && !is_meta(s[i]))
	{
		len++;
		i++;
	}
	return (len);
}

void	consume_after_redir(char *s, int *i)
{
	skip_ws(s, i);
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
		if (s[*i] == '\'')
			(*i)++;
	}
	else if (s[*i] == '\"')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\"')
			(*i)++;
		if (s[*i] == '\"')
			(*i)++;
	}
	else
		while (s[*i] && s[*i] != ' ' && s[*i] != '\t'
			&& s[*i] != '\'' && s[*i] != '\"'
			&& s[*i] != '>' && s[*i] != '<' && s[*i] != '|')
			(*i)++;
}

int	process_redir_if_any(char *s, int *i)
{
	char	op;

	if (s[*i] == '<' || s[*i] == '>')
	{
		op = s[*i];
		(*i)++;
		if (s[*i] == op)
			(*i)++;
		consume_after_redir(s, i);
		return (1);
	}
	return (0);
}
