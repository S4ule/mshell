/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:45:43 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/05 10:53:30 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**crash(int i, char **strs)
{
	while (--i >= 0)
		free(strs[i]);
	free(strs);
	return (0);
}

static int	world_cont(const char *str, char c)
{
	int	res;

	res = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
			res++;
		while (*str && *str != c)
			str++;
	}
	return (res);
}

static void	ft_strncpy(char *to, const char *from, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
	return ;
}

static int	ft_worldlen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		j;

	strs = malloc(sizeof(char *) * (world_cont(s, c) + 1));
	if (strs == 0)
		return (0);
	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			strs[j] = malloc(sizeof(char) * (ft_worldlen(s, c) + 1));
			if (strs[j] == 0)
				return (crash(j, strs));
			ft_strncpy(strs[j], s, ft_worldlen(s, c));
			s = s + ft_worldlen(s, c);
			j++;
		}
	}
	strs[j] = 0;
	return (strs);
}
