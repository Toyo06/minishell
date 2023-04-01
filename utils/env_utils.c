/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:05:48 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/01 13:20:41 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_node_env(char *name, char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->name = name;
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_next_node_env(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!*head)
	{
		(*head) = new_node;
		return ;
	}
	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
}

// void	printthelistenv(t_env **head)
// {
// 	t_env	*tmp;

// 	tmp = *head;
// 	while (tmp)
// 	{
// 		ft_printf("%s     ", tmp->name);
// 		ft_printf("%s\n", tmp->content);
// 		tmp = tmp->next;
// 	}
// }
