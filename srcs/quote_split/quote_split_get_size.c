/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:52:05 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 09:02:54 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_split.h"

static char	*get_size_bis_bis(char *str)
{
	while (*str != '\0' && *str != ' ' && \
		*str != '\"' && *str != '\'' && *str != '\\')
		str++;
	if (*str == '\'' && find_char(str + 1, '\'') != -1)
	{
		str++;
		while (*str != '\'')
			str++;
	}
	else if (*str == '\"' && find_end_quote(str + 1, '\"') != -1)
		str += find_end_quote(str + 1, '\"') + 2;
	return (str);
}

static char	*get_size_bis(char *str)
{
	int	check;

	check = 1;
	while (check != 0)
	{
		check = 0;
		str = get_size_bis_bis(str);
		if (*str == '\'' || *str == '\"')
		{
			str++;
			check = 1;
		}
		if (*str == '\\')
		{
			str++;
			if (*str)
				str++;
			check = 1;
		}
	}
	return (str);
}

//get the numbers of args in char *str
//return the numbers of args fond int char *str
size_t	get_size(char *str)
{
	size_t	output;

	output = 0;
	while (*str != '\0')
	{
		while (*str == ' ')
			str++;
		if (*str != '\0')
		{
			output++;
			str = get_size_bis(str);
		}
	}
	return (output);
}
