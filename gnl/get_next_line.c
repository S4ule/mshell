/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:05:47 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/20 09:22:53 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//free proprely
void	*ft_fail(char *line)
{
	free(line);
	return (0);
}

//try to find in str the end of the line, if is fond copy the rest part in buf
//return NULL if not fond, or return pointer at the start of str
char	*get_line(char **str, char *buff)
{
	char	*ptr;

	if (*str == 0)
		return (0);
	ptr = *str;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (*ptr == '\n')
	{
		*ptr = '\0';
		ptr++;
		while (*ptr)
		{
			*buff = *ptr;
			ptr++;
			buff++;
		}
		*buff = '\0';
		ptr = ft_line_copy(*str);
		free(*str);
		*str = ptr;
		return (*str);
	}
	return (0);
}

//start to init the line with buf (with the ft_init_fd fonction)
//read and stock in buffer, realloc the line with len_r value
//copy the buf in line with strcat
//verif if the end of the line is fond in line
//if line is at the end of the file return null
//if line is fond return line pointer
//if malloc or read fail return null and free with ft_fail
char	*get_start(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = {0};
	char		*line;
	ssize_t		len_r;

	if (ft_init_fd(&line, buf) == -1)
		return (0);
	len_r = -1;
	while (len_r != 0)
	{
		if (get_line(&line, buf) != 0)
			return (line);
		if (line == 0)
			return (0);
		len_r = read(fd, buf, BUFFER_SIZE);
		if (len_r == -1)
			return (ft_fail(line));
		buf[len_r] = '\0';
		ft_realloc_str(&line, len_r);
		if (line == 0)
			return (ft_fail(line));
		ft_strcat(line, buf);
		if (len_r == 0 && *line == '\0')
			return (ft_fail(line));
	}
	return (line);
}

//start of the fonction call, verif is the buffer size is invalid
char	*get_next_line(int fd)
{
	char	*line;

	line = 0;
	if (BUFFER_SIZE <= 0)
		return (0);
	line = get_start(fd);
	return (line);
}
