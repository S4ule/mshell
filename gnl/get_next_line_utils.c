/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:05:40 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/13 13:44:48 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//copy the from, in new malloced string
//if malloc fail return 0
char	*ft_line_copy(const char *from)
{
	size_t	i;
	char	*str;

	i = 0;
	while (from[i])
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (str == 0)
		return (0);
	i = 0;
	while (from[i])
	{
		str[i] = from[i];
		i++;
	}
	str[i] = '\n';
	i++;
	str[i] = '\0';
	return (str);
}

//copy the 'from' at the and of the 'to' string, and set the last + 1 at \0
void	ft_strcat(char *to, const char *from)
{
	while (*to)
		to++;
	while (*from)
	{
		*to = *from;
		to++;
		from++;
	}
	*to = '\0';
}

//re alloc the string poiter with (strlen + t + 1)
//copy the str into the new string and free(the original str)
//and set str with the new string allocated
//return NULL if malloc fail
void	ft_realloc_str(char **str, size_t t)
{
	char	*ptr;
	char	*new;
	size_t	i;

	i = 0;
	ptr = *str;
	while (ptr[i])
		i++;
	new = malloc(sizeof(char) * (i + t + 1));
	if (new == 0)
	{
		free(*str);
		*str = 0;
		return ;
	}
	i = 0;
	while (ptr[i])
	{
		new[i] = ptr[i];
		i++;
	}
	new[i] = ptr[i];
	*str = new;
	free(ptr);
}

//look the string in buf and ini line with buf value
//return size of string create or -1 if malloc fail
ssize_t	ft_init_fd(char **line, char *buff)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (buff[i])
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (ptr == 0)
		return (-1);
	ptr[0] = '\0';
	ft_strcat(ptr, buff);
	*line = ptr;
	buff[0] = '\0';
	return (i);
}
