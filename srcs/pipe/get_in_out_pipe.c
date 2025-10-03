/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_out_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:00:02 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/05 11:48:03 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_cmd.h"
#include "pipe.h"

static int	ft_perror_in_cmd(char *cmd, char *str, \
	unsigned char err, t_info *info)
{
	ft_perror(cmd, err, info);
	ft_perror(str, err, info);
	return (err);
}

static int	in_file_else(char *args_line, t_info *info, int *fd_in, size_t *i)
{
	char	*tmp;

	tmp = world_interpreter(args_line + *i + 1, " ", info);
	if (tmp == NULL)
		return (1);
	*fd_in = open(tmp, O_RDONLY);
	if (*fd_in == -1 && access(tmp, F_OK) == 0)
	{
		ft_perror_in_cmd(tmp, ": Permission denied\n", 1, info);
		free(tmp);
		return (1);
	}
	if (*fd_in == -1)
	{
		ft_perror_in_cmd(tmp, ": No such file or directory\n", 1, info);
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	in_file_pipe(char *args_line, t_info *info, int *fd_in, size_t *i)
{
	if (*fd_in != -1)
	{
		if (*fd_in != 0)
			close(*fd_in);
		*fd_in = -1;
	}
	if (args_line[*i + 1] == '<')
	{
		(*i)++;
		*fd_in = 0;
	}
	else
	{
		if (in_file_else(args_line, info, fd_in, i) == 1)
			return (1);
	}
	return (0);
}

static char	*out_file_doble(char *args_line, t_info *info, \
	int *fd_out, size_t *i)
{
	char	*tmp;

	tmp = world_interpreter(args_line + *i + 2, " ", info);
	if (tmp == NULL)
		return (NULL);
	*fd_out = open(tmp, O_CREAT | O_RDWR, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	free(tmp);
	if (*fd_out != -1)
	{
		tmp = get_next_line(*fd_out);
		while (tmp != NULL)
		{
			free(tmp);
			tmp = get_next_line(*fd_out);
		}
	}
	tmp = world_interpreter(args_line + *i + 2, " ", info);
	if (tmp == NULL)
		return (NULL);
	(*i)++;
	return (tmp);
}

char	*out_file_start(char *args_line, t_info *info, \
	int *fd_out, size_t *i)
{
	char	*tmp;

	if (args_line[*i + 1] == '>')
	{
		tmp = out_file_doble(args_line, info, fd_out, i);
		if (tmp == NULL)
			return (NULL);
	}
	else
	{
		tmp = world_interpreter(args_line + *i + 1, " ", info);
		if (tmp == NULL)
			return (NULL);
		*fd_out = open(tmp, O_TRUNC | O_CREAT | O_RDWR, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	return (tmp);
}
