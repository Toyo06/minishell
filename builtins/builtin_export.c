/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:02:57 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/09 13:00:17 by mayyildi         ###   ########.fr       */
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
			if (eq_flag == 0)
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
	if (eq_flag == 0)
		tmp = create_node_env(ft_strdup(name), ft_strdup(content));
	else
		tmp = create_node_env(ft_strdup(name), NULL);
	add_next_node_env(env, tmp);
}

int	check_export_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			i++;
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(t_list **lst, t_env **env)
{
	t_list	*tmp;
	char	*equal;
	int		eq_flag;

	eq_flag = 0;
	tmp = (*lst);
	while (tmp->next != NULL && tmp->next->data != 6)
	{
		tmp = tmp->next;
		if (!ft_isalpha(tmp->arg[0]) || !check_export_arg(tmp->arg))
		{
			error_msg(5);
			return ;
		}
		equal = ft_strchr(tmp->arg, '=');
		if (equal == NULL)
		{
			eq_flag = 1;
			ft_update_export(env, tmp->arg, NULL, eq_flag);
			continue ;
		}
		*equal = '\0';
		if (eq_flag == 0)
			ft_update_export(env, tmp->arg, equal + 1, eq_flag);
	}
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
