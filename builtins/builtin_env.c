/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:37:04 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/08 15:13:47 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env **env, t_list **lst)
{
	int		count;
	t_list	*tmp;

	tmp = (*lst);
	count = ft_strlen(tmp->arg);
	if (count < 3)
		count = 3;
	if (ft_strncmp(tmp->arg, "env", count) == 0)
		ft_printenv(env);
}

void	ft_printenv(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (tmp->name != NULL && tmp->content != NULL)
		{
			printf("%s", tmp->name);
			printf("=");
			printf("%s\n", tmp->content);
		}
		tmp = tmp->next;
	}
}
