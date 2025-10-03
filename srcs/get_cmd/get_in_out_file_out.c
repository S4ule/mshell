/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_out_file_out.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:59:36 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 11:50:55 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"

static int	ft_perror_in_cmd(char *cmd, char *str, \
	unsigned char err, t_info *info)
{
	ft_perror(cmd, err, info);
	ft_perror(str, err, info);
	return (err);
}

static char	*get_in_out_file_out_one(char *args_line, t_info *info, size_t *i)
{
	char	*tmp;

	tmp = world_interpreter(args_line + *i + 2, " ", info);
	if (tmp == NULL)
		return (NULL);
	info->fd_out = open(tmp, O_CREAT | O_RDWR, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	free(tmp);
	if (info->fd_out != -1)
	{
		tmp = get_next_line(info->fd_out);
		while (tmp != NULL)
		{
			free(tmp);
			tmp = get_next_line(info->fd_out);
		}
	}
	tmp = world_interpreter(args_line + *i + 2, " ", info);
	if (tmp == NULL)
		return (NULL);
	(*i)++;
	return (tmp);
}

static char	*get_in_out_file_out_two(char *args_line, t_info *info, size_t *i)
{
	char	*tmp;

	if (info->fd_out != -1)
	{
		if (info->fd_out != -2)
			close(info->fd_out);
		info->fd_out = -1;
	}
	if (args_line[*i + 1] == '>')
	{
		tmp = get_in_out_file_out_one(args_line, info, i);
		if (tmp == NULL)
			return (NULL);
	}
	else
	{
		tmp = world_interpreter(args_line + *i + 1, " ", info);
		if (tmp == NULL)
			return (NULL);
		info->fd_out = open(tmp, O_TRUNC | O_CREAT | O_RDWR, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	return (tmp);
}

int	get_in_out_file_out(char *args_line, t_info *info, size_t *i)
{
	char	*tmp;

	if (args_line[*i] == '>')
	{
		tmp = get_in_out_file_out_two(args_line, info, i);
		if (info->fd_out == -1)
		{
			if (access(tmp, F_OK) == 0)
				ft_perror_in_cmd(tmp, ": Permission denied\n", 1, info);
			else
				ft_perror_in_cmd(tmp, ": No such file or directory\n", 1, info);
			free(tmp);
			info->fd_out = -1;
			return (1);
		}
		free(tmp);
	}
	return (0);
}
