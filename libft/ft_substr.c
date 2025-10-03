/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:26:21 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/08 14:22:55 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i])
		i++;
	if (i > start)
		size = i - start;
	if (size > len)
		size = len;
	str = malloc(sizeof(char) * (size + 1));
	if (str == 0)
		return (0);
	i = -1;
	while (++i < size && s[start + i])
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}
