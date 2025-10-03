/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:51 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/07 10:23:28 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//you can do this one realy easy with itoa into putstr
void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	char			c;

	if (n < 0)
	{
		write(fd, "-", 1);
		num = n * -1;
	}
	else
		num = n;
	if (num > 9)
	{
		ft_putnbr_fd(num / 10, fd);
		num %= 10;
	}
	c = num + '0';
	write(fd, &c, 1);
}
