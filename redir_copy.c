/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:44:25 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/25 14:47:08 by edtataru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_name(char *s, size_t *i, char *dest, size_t *j)
{
	char	q;

	if (s[*i] == '\'' || s[*i] == '\"')
	{
		q = s[(*i)++];
		while (s[*i] && s[*i] != q)
			dest[(*j)++] = s[(*i)++];
		if (s[*i] == q)
			(*i)++;
		return ;
	}
	while (s[*i] && !is_name_delim(s[*i]))
		dest[(*j)++] = s[(*i)++];
}

void	fill_redir(char *s, size_t *i, char *dest)
{
	size_t	j;
	char	op;

	j = 0;
	op = s[*i];
	dest[j++] = s[(*i)++];
	if (s[*i] && s[*i] == op)
		dest[j++] = s[(*i)++];
	while (s[*i] == ' ')
		(*i)++;
	copy_name(s, i, dest, &j);
	dest[j] = '\0';
}

int	calc_redir_len(char *s, size_t i)
{
	size_t	len;
	size_t	p;

	len = 1;
	if (s[i + 1] && s[i + 1] == s[i])
		len = 2;
	p = i + len;
	while (s[p] == ' ')
		p++;
	if (s[p] == '\'' || s[p] == '\"')
		return (len + len_quoted(s, p));
	return (len + len_word(s, p));
}

char	*copy_if_redirection(char *str, size_t *i)
{
	char	*dest;
	size_t	len;

	dest = NULL;
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '|')
		return (NULL);
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		skip_quoted_block(str, i);
		return (NULL);
	}
	if (str[*i] != '<' && str[*i] != '>')
	{
		skip_to_word_end(str, i);
		return (NULL);
	}
	len = calc_redir_len(str, *i);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	fill_redir(str, i, dest);
	return (dest);
}
