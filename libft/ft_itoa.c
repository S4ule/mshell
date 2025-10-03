/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:11:14 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/05 11:38:02 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_calc(unsigned int n)
{
	int	res;

	res = 0;
	if (n == 0)
		res = 1;
	else
	{
		while (n)
		{
			n = n / 10;
			res++;
		}
	}
	return (res);
}

static char	*i_need_lines(int neg, char *res, int i, unsigned int num)
{
	if (neg == 1)
	{
		res[0] = '-';
		i += neg;
	}
	res[i] = '\0';
	i--;
	if (num == 0)
		res[i] = '0';
	while (num)
	{
		res[i] = num % 10 + '0';
		num = num / 10;
		i--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	int				neg;
	char			*res;
	int				i;

	neg = 0;
	if (n < 0)
	{
		neg = 1;
		num = n * -1;
	}
	else
		num = n;
	i = len_calc(num);
	res = malloc(sizeof(char) * (i + neg + 1));
	if (res == 0)
		return (0);
	return (i_need_lines(neg, res, i, num));
}
