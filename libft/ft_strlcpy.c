/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:10:16 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/04 15:47:57 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(src);
	if (i + 1 < size)
	{
		j = -1;
		while (++j < i + 1)
			dst[j] = src[j];
	}
	else if (size)
	{
		j = -1;
		while (++j < size - 1)
			dst[j] = src[j];
		dst[j] = '\0';
	}
	return (i);
}
