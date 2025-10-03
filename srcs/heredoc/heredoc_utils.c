/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:57:01 by sbalesme          #+#    #+#             */
/*   Updated: 2022/09/22 11:59:13 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

//do strjoin() and free the two string after that
char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*output;

	output = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (output);
}

//get the next line in the string and return the line in malloced string
//return NULL if malloc call fail
char	*get_next_line_in_str(char *str)
{
	size_t	i;
	char	*output;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	output = malloc(sizeof(char) * (i + 1));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		output[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		output[i] = '\n';
		i++;
	}
	output[i] = '\0';
	return (output);
}

int	add_history_readline(t_info *info)
{
	char	*line;

	if (info->args_line == NULL)
		return (0);
	if (info->heredoc == NULL && info->pipe_heredoc == NULL)
	{
		if (info->args_line[0] != '\0')
		{
			add_history(info->args_line);
			return (0);
		}
		return (0);
	}
	line = add_history_readline_five(info);
	if (line == NULL)
		return (1);
	if (line[0] != '\0')
		add_history(line);
	free(line);
	return (0);
}
