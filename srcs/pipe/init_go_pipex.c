/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_go_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:49:05 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/02 17:32:01 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_cmd.h"
#include "pipe.h"

int	init_fd_trash(char *args_line, t_info *info)
{
	info->fd_trash = open(".trash", O_TRUNC | O_CREAT | O_RDWR, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (info->fd_trash == -1)
	{
		free(info->args_line);
		free(args_line);
		info->args_line = NULL;
		return (1);
	}
	return (0);
}

int	init_pip(char *args_line, int *pip_size, int **pip, t_info *info)
{
	*pip = create_size_pipe(args_line, pip_size);
	if (*pip == NULL)
	{
		close(info->fd_trash);
		free(info->args_line);
		free(args_line);
		info->args_line = NULL;
		return (1);
	}
	free(info->args_line);
	info->args_line = args_line;
	args_line = NULL;
	return (0);
}

int	init_args(char ****args, int pip_size, int *pip, t_info *info)
{
	*args = malloc(sizeof(char **) * (pip_size + 2));
	if (*args == NULL)
	{
		close(info->fd_trash);
		free(info->args_line);
		info->args_line = NULL;
		return (free_all_malloc(pip, *args, pip_size, 1));
	}
	(*args)[pip_size + 1] = NULL;
	return (0);
}

char	**get_in_out_file_pip(char *args_line, t_info *info, \
	int *fd_in, int *fd_out)
{	
	size_t	i;

	*fd_in = -1;
	*fd_out = -1;
	if (args_line == NULL)
		return (NULL);
	i = 0;
	while (args_line[i] && args_line[i] != '\n')
	{
		i += ignore_quote(args_line + i, &i);
		if (args_line[i] == '\0')
			break ;
		if (args_line[i] == '<')
		{
			if (in_file_pipe(args_line, info, fd_in, &i) == 1)
				return (NULL);
		}
		else if (args_line[i] == '>')
		{
			if (out_file_pipe(args_line, info, fd_out, &i) == 1)
				return (NULL);
		}
		i++;
	}
	return (get_clean_args(args_line, info));
}

int	get_all_args(int *pip, char ***args, int pip_size, t_info *info)
{
	int		*pip_tmp;
	int		i;

	pip_tmp = malloc(sizeof(int) * ((pip_size + 1) * 2));
	if (pip_tmp == NULL)
		return (-1);
	i = 0;
	while (i < (pip_size + 1) * 2)
		pip_tmp[i++] = -1;
	i = 0;
	while (i < pip_size + 1)
	{
		if (get_all_args_start(pip_tmp, i, args, info) == -1)
			return (-1);
		i++;
	}
	get_all_args_heredoc(pip_tmp, pip, info, pip_size);
	get_all_args_put_in_pip(pip_tmp, pip, info, pip_size);
	if (info->args_line != NULL)
	{
		free(info->args_line);
		info->args_line = NULL;
	}
	free(pip_tmp);
	return (0);
}
