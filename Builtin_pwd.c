/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 08:13:16 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/28 11:32:08 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_base	g_base;

void	registerpwd(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
		{
			g_base.pwd.pwd = ft_strdup(tmp->content);
			printf("%s\n", g_base.pwd.pwd);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_pwd(t_list **lst)
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
		if (ft_strncmp(tmp->arg, "pwd", count) == 0)
			printf("%s\n", g_base.pwd.pwd);
		tmp = tmp->next;
	}
}
