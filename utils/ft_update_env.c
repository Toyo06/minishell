/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:54:46 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/08 14:59:59 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_env(t_env **env, char *name, char *content)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(content);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = create_node_env(ft_strdup(name), ft_strdup(content));
	add_next_node_env(env, tmp);
}
