/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:46:20 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/08 16:03:35 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == 0)
		return ((char *)big);
	i = -1;
	j = 0;
	while (++i <= len && big[i])
	{
		if (big[i] != little[j])
			continue ;
		while (i + j <= len && (big[i + j] == little[j] || little[j] == 0))
			if (little[j++] == 0)
				return ((char *)(big + i));
		j = 0;
	}
	return (0);
}
