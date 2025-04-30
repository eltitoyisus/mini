/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:12:25 by dacastil          #+#    #+#             */
/*   Updated: 2024/12/13 16:50:33 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node_temp;
	t_list	*cont_trans;

	new_list = NULL;
	node_temp = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		cont_trans = f(lst->content);
		node_temp = ft_lstnew(cont_trans);
		if (!node_temp)
		{
			ft_lstclear(&new_list, del);
			del(cont_trans);
			return (NULL);
		}
		ft_lstadd_back(&new_list, node_temp);
		lst = lst->next;
	}
	return (new_list);
}
