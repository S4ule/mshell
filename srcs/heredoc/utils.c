/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:05:24 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 18:53:53 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

//find_char look of char c in the char *str
//return -1 if don't find char c in the char *str
//or the index of the char c in char *str
ssize_t	find_char_heredoc(char *str, char c, char *charset)
{
	size_t	i;
	size_t	j;
	int		mode;

	i = 0;
	mode = 0;
	while (str[i] != '\0')
	{
		if (mode != 0)
			mode--;
		j = 0;
		while (charset[j] && mode == 0)
		{
			if (str[i] == charset[j])
				mode = 2;
			j++;
		}
		if (mode == 0 && str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	size_of_heredoc(char **heredoc)
{
	int	i;

	i = 0;
	while (heredoc[i] != NULL)
		i++;
	return (i);
}

static char	**realloc_heredoc_for_fd(t_info *info)
{
	char	**output;
	int		i;

	if (info->heredoc == NULL)
		return (NULL);
	output = malloc(sizeof(char *) * size_of_heredoc(info->heredoc));
	if (output == NULL)
	{
		info->heredoc = free_args(info->heredoc, -1);
		return (NULL);
	}
	i = 0;
	while (info->heredoc[i + 1] != NULL)
	{
		output[i] = info->heredoc[i + 1];
		i++;
	}
	output[i] = NULL;
	free(info->heredoc[0]);
	free(info->heredoc);
	info->heredoc = output;
	return (output);
}

int	get_heredoc_fd(t_info *info, int num)
{
	int	fd;

	if (num == 1)
	{
		fd = open(".heredoc", O_TRUNC | O_CREAT | O_RDWR, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	else
	{
		if (info->heredoc != NULL)
			write(num, info->heredoc[0], ft_strlen(info->heredoc[0]));
		fd = -1;
	}
	if (fd != -1)
	{
		if (info->heredoc != NULL)
			write(fd, info->heredoc[0], ft_strlen(info->heredoc[0]));
		close(fd);
		fd = -1;
		fd = open(".heredoc", O_CREAT | O_RDWR, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	info->heredoc = realloc_heredoc_for_fd(info);
	return (fd);
}
