/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:22:31 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/28 18:42:05 by mayyildi         ###   ########.fr       */
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
		if (ft_strcmp(str, tmp->name) == 0)
		{
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
	while (tmp->next)
	{
		tmp = tmp->next;
		if (!ft_isalpha(tmp->arg[0]) || !check_alnum(tmp->arg))
		{
			if (tmp->data == 6)
				break ;
			err_msg_unset(9);
			exit_condition(1);
			if (tmp->next)
				continue ;
			return ;
		}
		ft_unset(env, tmp->arg);
	}
	exit_condition(0);
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
