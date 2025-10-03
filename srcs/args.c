/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 09:11:11 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/06 09:59:08 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_perror_and_args(const char *str, int err, t_info *info)
{
	if (str != NULL)
		write(2, str, ft_strlen(str));
	info->err = err;
	return (1);
}

static int	check_args_line_moremore(char *str, t_info *info)
{
	int	i;
	int	j;

	i = 1;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
		{
			j = i + 1;
			while (str[j])
			{
				if (!ft_isalnum(str[j]) && !ft_isalpha(str[j]) && \
				str[j] != ' ')
					check_and_result(str, j, info);
				j++;
			}
		}
		i++;
	}
	return (0);
}

static int	check_args_line_more(char *str, t_info *info)
{
	int	i;
	int	j;

	i = 3;
	if (str == NULL || ft_strlen(str) < 3)
		return (0);
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '\0') || (str[i] == '>' \
		&& str[i + 1] == '\0'))
			return (check_and_resultt(str, i, info));
		if ((str[i] == '>' || str[i] == '<'))
		{
			j = i + 1;
			while (str[j++])
			{
				if (str[j] == ' ')
					j++;
				if (str[j] == '|' && (str[j -1] == '<'))
					return (ft_perror_and_args(" syntax error near \
					unexpected token `|'\n", 2, info));
			}
		}	
		i++;
	}
	return (0);
}

static int	check_and_redirect(char *str, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		while (str[j] == '<')
			j++;
		if (check_j(j, info))
			return (1);
		i++;
	}
	return (0);
}

int	check_args_line(char *str, t_info *info)
{
	if (str == NULL)
		return (0);
	if (check_and_redirect(str, info) == 1)
		return (1);
	if (check_if_not_empty(str) == 1 || check_args_line_more(str, info) == 1 || \
	check_args_line_moremore(str, info) == 1)
		return (1);
	if (str[0] == '|')
		return (ft_perror_and_args(" syntax error near unexpected token `|'\n", \
		2, info));
	if ((str[0] == '>' && str[1] == '\0') || (str[0] == '>' && str[2] == '\0' \
	&& str[1] == '>') || (str[0] == '<' && str[1] == '\0') || (str[0] == '<' \
	&& str[2] == '\0' && str[1] == '<') || (str[0] == '<' && str[1] == '<' && \
	str[2] == '<' && str[3] == '\0'))
		return (ft_perror_and_args(\
		" syntax error near unexpected token `newline'\n", 2, info));
	if (str[0] == '>' && str[1] == '>' && str[2] == '>' && str[3] == '\0')
		return (ft_perror_and_args(\
		" syntax error near unexpected token `>'\n", 2, info));
	return (0);
}
