/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:22:31 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/08 18:34:28 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unset_arg(char *str)
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

void	ft_unset(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (ft_strcmp(str, tmp->name) == 0
			|| ft_strcmp(str, tmp->content) == 0)
		{
			// if (!ft_isalpha(tmp->content[0]) || !check_unset_arg(tmp->content))
			// {
			// 	error_msg(5);
			// 	return ;
			// }
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			if (tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			tmp->next = NULL;
			tmp->prev = NULL;
			free(tmp->name);
			if (tmp->content)
				free(tmp->content);
			free(tmp);
		}
		tmp = tmp->next;
	}
}

void	check_unset(t_list **lst, t_env **env)
{
	t_list	*tmp;

	tmp = (*lst);
	tmp = tmp->next;
	while (tmp)
	{
		if (!check_alnum(tmp->arg))
		{
			error_msg(1);
			return ;
		}
		ft_unset(env, tmp->arg);
		tmp = tmp->next;
	}
}

int	check_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}
