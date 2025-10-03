/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_size_pipe.c                                 :+:      :+:    :+:   */
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

static int	*create_size_pipe_bis(int pipe_size)
{
	int	*pip;
	int	i;

	pip = malloc(sizeof(int) * (pipe_size * 2));
	if (pip == NULL)
		return (NULL);
	i = 0;
	while (i < (pipe_size))
	{
		if (pipe(pip + i * 2) < 0)
		{
			i = (i * 2) - 1;
			while (i >= 0)
				close(pip[i--]);
			free(pip);
			return (NULL);
		}
		i++;
	}
	return (pip);
}

int	*create_size_pipe(char *args_line, int *pipe_size)
{
	size_t	j;

	(*pipe_size) = 0;
	j = 0;
	while (args_line[j])
	{
		j += ignore_quote(args_line + j, &j);
		if (args_line[j] == '|')
			(*pipe_size)++;
		if (args_line[j])
			j++;
	}
	args_line += j;
	return (create_size_pipe_bis(*pipe_size));
}
