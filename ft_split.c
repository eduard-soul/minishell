/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:39:46 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/23 02:28:10 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_path(char *str, char delim)
{
	char	**result;
	int		i;
	int		j;
	int		nb_words;

	nb_words = count_words(str, delim);
	result = malloc(sizeof(char *) * (nb_words + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < nb_words)
	{
		if (j == 0)
			i = skip_prefix(str, i);
		result[j] = ft_malloc_len_word(str, i, delim);
		if (result[j] == NULL)
			return (free_split(result, j));
		i = ft_fill_word(result[j], str, i, delim);
		j++;
	}
	result[j] = NULL;
	return (result);
}
