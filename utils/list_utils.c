/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:58:01 by mayyildi          #+#    #+#             */
/*   Updated: 2023/02/10 17:50:51 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node(t_list **head, int nb, char *str)
{
	(*head) = malloc(sizeof(t_list));
	(*head)->data = nb;
	(*head)->arg = str;
	(*head)->next = NULL;
	(*head)->prev = NULL;
}

void	add_next_node(t_list **head, t_list *new_node)
{
	t_list	*tmp;

	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
}

int	count_list(t_list **head)
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

t_list	*free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->arg);
		free(lst);
		lst = tmp;
	}
	return (lst);
}

// void	printthelist(t_list **head)
// {
// 	t_list	*tmp;

// 	tmp = *head;
// 	while (tmp)
// 	{
// 		ft_printf("%d     ", tmp->data);
// 		ft_printf("%s\n", tmp->arg);
// 		tmp = tmp->next;
// 	}
// }
