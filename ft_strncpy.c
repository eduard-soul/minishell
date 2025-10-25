/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:54:51 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/25 14:34:59 by edtataru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *s1, int start, int len)
{
	char	*dest;
	size_t	i;
	size_t	j;

	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	i = (size_t)start;
	j = 0;
	while (i < (size_t)start + (size_t)len)
		dest[j++] = s1[i++];
	dest[j] = 0;
	return (dest);
}
