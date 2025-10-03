/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:09:43 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/04 13:01:31 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	ptr_dst = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	if (ptr_dst > ptr_src && ptr_dst - ptr_src < (long int)n)
	{
		n--;
		while ((long int)n >= 0)
		{
			ptr_dst[n] = ptr_src[n];
			n--;
		}
		return (dest);
	}
	while (n > 0)
	{
		*ptr_dst = *ptr_src;
		ptr_dst++;
		ptr_src++;
		n--;
	}
	return (dest);
}
