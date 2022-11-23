/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tool_list_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:02:43 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/23 12:00:13 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	addnodeenv(t_list **head, char	*name, char *content)
{
	(*head) = malloc(sizeof(t_list));
	(*head)->name = name;
	(*head)->content = content;
	(*head)->next = NULL;
	(*head)->prev = NULL;
}

void	printthelistenv(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		ft_printf("%s     ", tmp->name);
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
