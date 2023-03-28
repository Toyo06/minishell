/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:02:57 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/28 00:03:10 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_export(t_env **env, char *name, char *content, int eq_flag)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			if (eq_flag == 1)
			{
				free(tmp->content);
				tmp->content = ft_strdup(content);
			}
			else if (!tmp->content)
				tmp->content = NULL;
			return ;
		}
		tmp = tmp->next;
	}
	if (eq_flag == 1)
		tmp = create_node_env(ft_strdup(name), ft_strdup(content));
	else
		tmp = create_node_env(ft_strdup(name), NULL);
	add_next_node_env(env, tmp);
}

void	ft_export(t_list **lst, t_env **env)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp->next != NULL && tmp->next->data != 6)
	{
		g_base.xport.eq_fl = 1;
		tmp = tmp->next;
		if (!check_arg_validity(tmp->arg))
			continue ;
		g_base.xport.eq = ft_strchr(tmp->arg, '=');
		if (g_base.xport.eq == NULL)
		{
			g_base.xport.eq_fl = 0;
			if (!check_arg_validity(tmp->arg))
				continue ;
			ft_update_export(env, tmp->arg, NULL, g_base.xport.eq_fl);
			continue ;
		}
		*g_base.xport.eq = '\0';
		g_base.xport.arg = get_arg(g_base.xport.eq, env);
		ft_update_export(env, tmp->arg, g_base.xport.arg, g_base.xport.eq_fl);
		free(g_base.xport.arg);
	}
	exit_condition(0);
}

void	ft_printexport(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (tmp->name != NULL)
		{
			printf("declare -x ");
			printf("%s", tmp->name);
			if (tmp->content)
			{
				printf("=");
				printf("\"");
				printf("%s", tmp->content);
				printf("\"");
			}
			printf("\n");
		}
		if (tmp->name == NULL)
		{
			printf("declare -x ");
			printf("%s\n", tmp->content);
		}
		tmp = tmp->next;
	}
}
