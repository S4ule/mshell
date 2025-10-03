/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:05:55 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/16 12:12:04 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

void	ft_realloc_str(char **str, size_t t);

void	ft_strcat(char *to, const char *from);

char	*get_next_line(int fd);

char	*get_start(int fd);

char	*get_line(char **str, char *buf);

char	*ft_line_copy(const char *from);

ssize_t	ft_init_fd(char **line, char *buf);

void	*ft_fail(char *line);

#endif
