/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:49:05 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/01 17:44:41 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_cmd.h"
#include "pipe.h"

static void	get_all_args_heredoc_last(int *pip_tmp, int *pip, \
	t_info *info, int i)
{
	if (pip_tmp[i] == 0)
	{
		get_heredoc_fd(info, pip[i - 2]);
		if (info->heredoc == NULL)
			ft_perror("error: realloc hereodc in get_heredoc_fd\n", 1, info);
		if (pip_tmp[i - 1] == -1)
			pip_tmp[i - 1] = info->fd_trash;
	}
	else if (pip_tmp[i] == -2)
	{
		if (i % 2 != 0 && i > 2)
			pip_tmp[i - 2] = info->fd_trash;
		pip_tmp[i] = -1;
	}
}

void	get_all_args_heredoc(int *pip_tmp, int *pip, \
	t_info *info, int pip_size)
{
	int	i;

	i = 0;
	while (i < (pip_size + 1) * 2)
	{
		if (pip_tmp[i] == 0 && i == 0)
		{
			pip_tmp[i] = get_heredoc_fd(info, 1);
			if (info->heredoc == NULL)
			{
				if (pip_tmp[i] != -1)
					close(pip_tmp[i]);
				ft_perror("error: realloc hereodc in get_heredoc_fd\n", 1, info);
				pip_tmp[i] = -2;
			}
			if (pip_tmp[i] == -1)
			{
				ft_perror("error: impossible to open .heredoc\n", 1, info);
				pip_tmp[i] = info->fd_trash;
			}
		}
		else
			get_all_args_heredoc_last(pip_tmp, pip, info, i);
		i++;
	}
}

static void	get_all_args_put_in_pip_last(int *pip_tmp, int *pip, int i)
{
	if (pip_tmp[i] != 0 && i % 2 == 0)
	{
		close(pip[i - 2]);
		pip[i - 2] = pip_tmp[i];
	}
	else if (pip_tmp[i] != 0 && i % 2 != 0)
	{
		close(pip[i]);
		pip[i] = pip_tmp[i];
	}
}

void	get_all_args_put_in_pip(int *pip_tmp, int *pip, \
	t_info *info, int pip_size)
{
	int	i;

	i = 0;
	while (i < (pip_size + 1) * 2)
	{
		if (pip_tmp[i] == -1)
		{
			if (i == 0)
				info->fd_in = 0;
			else if (i == (pip_size + 1) * 2 - 1)
				info->fd_out = 1;
		}
		else if (i == 0)
			info->fd_in = pip_tmp[0];
		else if (i == (pip_size + 1) * 2 - 1)
			info->fd_out = pip_tmp[i];
		else
			get_all_args_put_in_pip_last(pip_tmp, pip, i);
		i++;
	}
}
