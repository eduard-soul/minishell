/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:54:51 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/20 19:26:45 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *s1, int start, int len)
{
	char	*dest;
	int		i;
	int		j;

	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	i = start;
	j = 0;
	while (i < start + len)
		dest[j++] = s1[i++];
	dest[j] = 0;
	return (dest);
}
