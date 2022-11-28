/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:43:42 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/28 11:54:30 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_env(t_env **env, t_list **lst)
{
	t_list	*tmp;
	int		count;

	tmp = (*lst);
	count = 3;
	while (tmp)
	{
		count = ft_strlen(tmp->arg);
		if (count < 3)
			count = 3;
		if (ft_strncmp(tmp->arg, "env", count) == 0)
			ft_printenv(env);
		tmp = tmp->next;
	}
}

void	ft_printenv(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		printf("%s", tmp->name);
		printf("=");
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
