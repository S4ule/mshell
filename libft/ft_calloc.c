/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:53:53 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/09 11:26:59 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;

	if (nmemb != 0 && size != 0)
	{
		if (((unsigned int)size * (unsigned int)nmemb) / \
			(unsigned int)nmemb != (unsigned int)size)
			return (0);
	}
	res = malloc(size * nmemb);
	if (res == 0)
		return (0);
	ft_bzero(res, size * nmemb);
	return (res);
}
