/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:42:43 by edesprez          #+#    #+#             */
/*   Updated: 2025/10/25 14:35:00 by edtataru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_until_char(char *str, int *i, char c, int *failed_malloc)
{
	char	*dest;
	size_t	j;

	j = 0;
	while (str[*i + j] && str[*i + j] != c)
		j++;
	dest = malloc(sizeof(char) * (j + 1));
	if (!dest)
	{
		*failed_malloc = 1;
		return (NULL);
	}
	j = 0;
	while (str[*i] && str[*i] != c)
		dest[j++] = str[(*i)++];
	if (str[*i] && str[*i] == c)
		(*i)++;
	dest[j] = '\0';
	return (dest);
}

void	skip_ws(char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
}

char	*read_segment(char *s, int *i, int *failed)
{
	int		start;
	char	*seg;

	if (s[*i] == '\'')
	{
		(*i)++;
		return (copy_until_char(s, i, '\'', failed));
	}
	if (s[*i] == '\"')
	{
		(*i)++;
		return (copy_until_char(s, i, '\"', failed));
	}
	start = *i;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t'
		&& s[*i] != '|' && s[*i] != '<' && s[*i] != '>'
		&& s[*i] != '\'' && s[*i] != '\"')
		(*i)++;
	seg = ft_strncpy(s, start, *i - start);
	if (!seg)
		*failed = 1;
	return (seg);
}

int	append_seg(char **dest, char *seg, int *failed)
{
	char	*tmp;

	if (!*dest)
	{
		*dest = seg;
		return (1);
	}
	tmp = ft_strjoin(*dest, seg);
	free(*dest);
	free(seg);
	*dest = tmp;
	if (!*dest)
	{
		*failed = 1;
		return (0);
	}
	return (1);
}

char	*copy_if_arg(char *str, int *i, int *failed_malloc)
{
	char	*dest;
	char	*seg;

	*failed_malloc = 0;
	skip_ws(str, i);
	if (str[*i] == '|' || str[*i] == '\0')
		return (NULL);
	if (process_redir_if_any(str, i))
		return (NULL);
	dest = NULL;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
	{
		seg = read_segment(str, i, failed_malloc);
		if (*failed_malloc || !seg)
		{
			free(dest);
			*failed_malloc = 1;
			return (NULL);
		}
		if (!append_seg(&dest, seg, failed_malloc))
			return (NULL);
	}
	return (dest);
}
