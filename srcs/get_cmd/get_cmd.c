/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:09:30 by sbalesme          #+#    #+#             */
/*   Updated: 2022/09/22 12:11:06 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"
#include "quote_split.h"

static void	re_create_args_line_bis(char *args_line, char *buf, char *tmp)
{
	int	i;
	int	j;

	i = -1;
	while (args_line[++i] != '\0')
	{
		if (args_line[i] == '\n')
			tmp[i] = ' ';
		else
			tmp[i] = args_line[i];
	}
	j = -1;
	while (buf[++j])
	{
		if (buf[j] == '\n')
			tmp[i++] = ' ';
		else
			tmp[i++] = buf[j];
	}
	tmp[i] = '\0';
}

//re create the args_line with the next pipe_heredoc
//return null if malloc fail
//else return the string with no '\n' (replace with space)
char	*re_create_args_line(char *args_line, t_info *info)
{
	char	*tmp;
	char	*buf;

	buf = get_next_pipe_heredoc(info);
	if (buf == NULL)
		return (NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(args_line) + ft_strlen(buf) + 1));
	if (tmp == NULL)
	{
		free(buf);
		return (NULL);
	}
	re_create_args_line_bis(args_line, buf, tmp);
	free(args_line);
	free(buf);
	return (tmp);
}

size_t	find_exec_mode(char *args_line)
{
	size_t	i;

	i = 0;
	while (args_line[i])
	{
		i += ignore_quote(args_line + i, &i);
		if (args_line[i] == '|')
			return (1);
		if (args_line[i])
			i++;
	}
	return (0);
}

static int	pars_cmd_bis(char *args_line, t_info *info, int mode)
{
	while (look_for_pipe_end(args_line, ft_strlen(args_line)) == 0)
	{
		args_line = re_create_args_line(args_line, info);
		if (args_line == NULL)
			return (2);
	}
	mode = find_exec_mode(args_line);
	if (mode == 0)
		go_cmd(args_line, info, 0);
	if (mode == 1)
	{
		if (go_pipex(args_line, info, 0) == 2)
			ft_perror("error: impossible to init pipe files\n", 1, info);
	}
	return (0);
}

//start of the fonction call
//that pars the args_line and pipe_heredoc
//too call cmd_start and pipex with args
int	pars_cmd(char *args_line, t_info *info)
{
	int	err;

	if (args_line == NULL)
		return (1);
	args_line = get_next_line_in_str(args_line);
	if (args_line == NULL)
		return (1);
	if (args_line[ft_strlen(args_line) - 1] == '\n')
		args_line[ft_strlen(args_line) - 1] = '\0';
	while (1)
	{
		err = pars_cmd_bis(args_line, info, 0);
		if (err == 2)
			return (1);
		args_line = NULL;
		if (args_line == NULL && info->pipe_heredoc == NULL)
			break ;
		else
		{
			args_line = get_next_pipe_heredoc(info);
			if (args_line == NULL)
				break ;
		}
	}
	return (0);
}
