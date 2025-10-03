/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:59:36 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 11:52:41 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"

//interprete the world in str with charset
//that gonna get the world with the
//get_world_with_quote() fonction call
//and after that is str in not at the end of
//the str and look for some unexpected token
//return NULL if malloc fail
char	*world_interpreter(char *str, char *charset, t_info *info)
{
	size_t	i;
	char	*tmp;

	if (str == NULL)
		return (NULL);
	tmp = get_world_with_quote(str, charset);
	if (tmp == NULL)
		return (NULL);
	if (check_end(tmp, charset) == 1)
	{
		free(tmp);
		return (NULL);
	}
	i = 0;
	while (tmp[i] == ' ')
		i++;
	if (test_charset(tmp[i], "<>|\n") == 0)
	{
		ft_perror("bash: syntax error near unexpected token\n", 1, info);
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

static int	osf_line_needed(char *args_line, t_info *info, size_t *i)
{
	if (get_in_out_file_in(args_line, info, i) == 1)
		return (1);
	if (get_in_out_file_out(args_line, info, i) == 1)
		return (1);
	return (0);
}

//pars the args_line
//get the info->fd_in and info->fd_out
//after that the fonction call get_clean_args
//return NULL if that fail in one part
char	**get_in_out_file(char *args_line, t_info *info)
{
	size_t	i;

	if (args_line == NULL)
		return (NULL);
	i = 0;
	while (args_line[i] && args_line[i] != '\n')
	{
		i += ignore_quote(args_line + i, &i);
		if (args_line[i] == '\0')
			break ;
		if (osf_line_needed(args_line, info, &i) == 1)
			return (NULL);
		i++;
	}
	if (info->fd_in == -2 || info->fd_out == -2)
	{
		if (info->fd_in != -2 && info->fd_in != -1)
			close(info->fd_in);
		if (info->fd_out != -2 && info->fd_out != -1)
			close(info->fd_out);
		info->fd_in = -1;
		info->fd_out = -1;
		return (NULL);
	}
	return (get_clean_args(args_line, info));
}

static char	**realloc_clean_args(char **args, int size)
{
	int		i;
	char	**output;

	i = 0;
	while (args[i])
		i++;
	output = malloc(sizeof(char *) * (i - size + 1));
	if (output == NULL)
	{
		args = free_args(args, -1);
		return (NULL);
	}
	i = size;
	while (--i >= 0)
		free(args[i]);
	i = 0;
	while (args[size])
		output[i++] = args[size++];
	output[i] = NULL;
	free(args);
	args = NULL;
	return (output);
}

//get clean args create a string with args_line with no doc
//exp : "cat test << test > res"
//to : "cat test  "
//after that call quote_split
//that gonna split that line to get :
// [0] "cat"
// [1] "test"
// [2] NULL
//return NULL if fail in one part
char	**get_clean_args(char *args_line, t_info *info)
{
	size_t	i;
	ssize_t	size;
	char	*line;
	char	**output;

	size = get_size_clean_args(args_line);
	line = malloc(sizeof(char) * (size + 1));
	if (line == NULL)
		return (NULL);
	line = get_clean_args_bis(args_line, line);
	output = quote_split(line, info);
	free(line);
	i = 0;
	while (output != NULL && output[i] != NULL && \
		check_if_not_empty(output[i]) == 1)
		i++;
	if ((output != NULL && i != 0 && output[i] == NULL) \
		|| (output != NULL && output[0] == NULL))
	{
		output = free_args(output, -1);
		info->err = 0;
	}
	else if (output != NULL && i != 0)
		output = realloc_clean_args(output, i);
	return (output);
}
