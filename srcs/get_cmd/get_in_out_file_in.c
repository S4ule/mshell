/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_out_file_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:59:36 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 11:50:44 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"

static int	ft_perror_in_out(char *cmd, char *str, \
	unsigned char err, t_info *info)
{
	ft_perror(cmd, err, info);
	ft_perror(str, err, info);
	return (err);
}

static int	get_in_out_file_in_one(t_info *info, size_t *i)
{
	info->fd_in = get_heredoc_fd(info, 1);
	(*i)++;
	if (info->heredoc == NULL)
	{
		if (info->fd_in != -1)
		{
			close(info->fd_in);
			info->fd_in = -1;
		}
		ft_perror("error: realloc hereodc in get_heredoc_fd\n", 1, info);
		return (1);
	}
	else if (info->fd_in == -1)
	{
		ft_perror("error: impossible to open .heredoc\n", 1, info);
		return (1);
	}
	return (0);
}

static int	get_in_out_file_in_two(char *args_line, t_info *info, size_t *i)
{
	char	*tmp;

	tmp = world_interpreter(args_line + *i + 1, " ", info);
	if (tmp == NULL)
		return (1);
	info->fd_in = open(tmp, O_RDONLY);
	if (info->fd_in == -1 && access(tmp, F_OK) == 0)
	{
		ft_perror_in_out(tmp, ": Permission denied\n", 1, info);
		info->fd_in = -1;
		free(tmp);
		return (1);
	}
	if (info->fd_in == -1)
	{
		ft_perror_in_out(tmp, ": No such file or directory\n", 1, info);
		info->fd_in = -1;
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	get_in_out_file_in(char *args_line, t_info *info, size_t *i)
{
	if (args_line[*i] == '<')
	{
		if (info->fd_in != -1)
		{
			if (info->fd_in != -2)
				close(info->fd_in);
			info->fd_in = -1;
		}
		if (args_line[*i + 1] == '<')
		{
			if (get_in_out_file_in_one(info, i) == 1)
				return (1);
		}
		else
			if (get_in_out_file_in_two(args_line, info, i) == 1)
				return (1);
	}
	return (0);
}
