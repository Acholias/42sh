/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:47:05 by lumugot           #+#    #+#             */
/*   Updated: 2024/10/18 16:02:31 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*stock;
	t_list	*next;

	if (!lst || !del)
		return ;
	stock = *lst;
	while (stock)
	{
		next = stock->next;
		del (stock->content);
		free(stock);
		stock = next;
	}
	*lst = NULL;
}
