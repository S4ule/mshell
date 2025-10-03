/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:17:17 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/05 08:17:06 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_split.h"

//find_char look of char c in the char *str
//return -1 if don't find char c in the char *str
//or the index of the char c in char *str
ssize_t	find_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

//find_char look of char c in the char *str
//return -1 if don't find char c in the char *str
//or the index of the char c in char *str
//that skip the "\"" in quote to secure the look
ssize_t	find_end_quote(char *str, char c)
{
	size_t	i;
	int		mode;

	i = 0;
	while (str[i] != '\0')
	{
		mode = 0;
		if (str[i] == '\\')
		{
			mode = 1;
			i++;
			if (str[i] == '\0')
				break ;
		}
		if (str[i] == c && mode != 1)
			return (i);
		i++;
	}
	return (-1);
}

char	get_back_slach(char *str, int *step)
{
	if (*str != '\\')
		return (-1);
	str++;
	if (*str == '\0' || *str == ' ')
		return (-1);
	*step = 2;
	if (*str == '\\')
		return (92);
	if (*str == '$')
		return (36);
	if (*str == '\'')
		return (39);
	if (*str == '\"')
		return (34);
	return (*str);
}
