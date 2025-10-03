/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:43:43 by sbalesme          #+#    #+#             */
/*   Updated: 2022/05/04 12:34:25 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*ptr;

	start = 0;
	while (lst)
	{
		ptr = ft_lstnew((*f)(lst->content));
		if (ptr == 0)
		{
			ft_lstclear(&start, del);
			return (0);
		}
		ft_lstadd_back(&start, ptr);
		lst = lst->next;
	}
	return (start);
}
