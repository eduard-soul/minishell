/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edtataru <edtataru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:51:32 by edtataru          #+#    #+#             */
/*   Updated: 2025/10/15 13:52:33 by edtataru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_atoi(int nb)
{
	char	*dest;
	int		len;
	int		tmp;

	if (nb < 0)
		return (0);
	tmp = nb;
	len = 1;
	if (nb == 0)
		len++;
	while (tmp)
	{
		tmp = tmp / 10;
		len++;
	}
	dest = malloc(sizeof(char) * len);
	if (!dest)
		return (0);
	dest[len - 1] = 0;
	while (len > 1)
	{
		dest[len-- - 2] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (dest);
}
