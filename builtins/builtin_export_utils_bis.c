/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils_bis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:03:24 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/11 17:30:14 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	sp_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	check_arg_validity(char *str)
{
	int	i;

	i = 0;
	if (!str || !ft_isalpha(str[i]))
	{
		if (ft_strcmp(str, "<") == 0)
			return (0);
		err_msg_export(5);
		return (0);
	}
	return (1);
}

void	print_export_condition(t_list *tmp, t_env **env, int fd)
{
	if (tmp->next && g_base.xport.disp2 == 0)
		ft_printexport(env, fd);
}
