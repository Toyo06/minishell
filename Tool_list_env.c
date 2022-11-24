/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tool_list_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:02:43 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/24 08:37:26 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	addnodeenv(t_env **head, char *name, char *content)
{
	(*head) = malloc(sizeof(t_list));
	(*head)->name = name;
	(*head)->content = content;
	(*head)->next = NULL;
	(*head)->prev = NULL;
}

void	printthelistenv(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		ft_printf("%s     ", tmp->name);
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	addnextnodeenv(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
}

void	unsetonlistenv(t_env **env, char *str)
{
	while ((*env)->next)
	{
		if (ft_strncmp(str, (*env)->name, ft_strlen(str)) == 0)
			(*env)->name = NULL;
		(*env) = (*env)->next;
	}
	while ((*env)->prev)
		(*env) = (*env)->prev;
}
