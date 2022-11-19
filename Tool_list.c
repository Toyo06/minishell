/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tool_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:40:37 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/18 23:55:40 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	addnode(t_list **head, int nb, char *str)
{
	(*head) = malloc(sizeof(t_list));
	(*head)->data = nb;
	(*head)->arg = str;
	(*head)->next = NULL;
	(*head)->prev = NULL;
}

void	addnextnode(t_list **head, t_list *new_node)
{
	t_list	*tmp;

	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
}

void	printthelist(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		ft_printf("%d     ", tmp->data);
		ft_printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
}

int	countlist(t_list **head)
{
	int		i;
	t_list	*tmp;

	tmp = (*head);
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_list	*freelist(t_list *lst)
{
	while (lst)
	{
		free(lst->arg);
		free(lst);
		lst = lst->next;
	}
	return (lst);
}
