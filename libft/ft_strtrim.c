/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:39:38 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/05 10:26:25 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static unsigned int	calclen(char const *s1, char const *set)
{
	int	res;

	res = 0;
	while (s1[res])
		res++;
	if (res)
	{
		res--;
		while (isset(s1[res], set) == 1 && res > 0)
			res--;
		res++;
		return (res);
	}
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	len;
	unsigned int	i;
	char			*str;

	while (isset(*s1, set) == 1)
		s1++;
	len = calclen(s1, set);
	str = malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
