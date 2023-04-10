/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:02:57 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 20:20:24 by sroggens         ###   ########.fr       */
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

void	ft_export(t_list **lst, t_env **env, int fd)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp->next && tmp->data != 6)
	{
		tmp = tmp->next;
		if (tmp->data != 10 && tmp->data != 12)
		{
			if (tmp->next && g_base.xport.disp2 == 0)
				ft_printexport(env, fd);
			continue ;
		}
		g_base.xport.eq_fl = 1;
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

static t_env	*find_next_min(t_env *env, const char *prev_min)
{
	t_env	*tmp;
	t_env	*min;

	min = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, prev_min) > 0
			&& (min == NULL || ft_strcmp(tmp->name, min->name) < 0))
		{
			min = tmp;
		}
		tmp = tmp->next;
	}
	return (min);
}

static void	print_env_node(t_env *node, int fd)
{
	if (node->name != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(node->name, fd);
		if (node->content)
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd("\"", fd);
			ft_putstr_fd(node->content, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
	}
	else
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(node->content, fd);
		ft_putstr_fd("\n", fd);
	}
}

void	ft_printexport(t_env **env, int fd)
{
	t_env	*min;
	char	*prev_min;

	prev_min = NULL;
	min = find_next_min(*env, prev_min);
	while (min != NULL)
	{
		print_env_node(min, fd);
		free(prev_min);
		prev_min = ft_strdup(min->name);
		min = find_next_min(*env, prev_min);
	}
	free(prev_min);
}
