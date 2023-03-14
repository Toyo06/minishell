/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils_bis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:03:24 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/14 18:27:17 by mayyildi         ###   ########.fr       */
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
	if (!ft_isalpha(str[i]))
	{
		err_msg_export(5);
		return (0);
	}
	while (str[i])
	{
		if (sp_check(str))
		{
			err_msg_export(5);
			return (0);
		}
		i++;
	}
	return (1);
}
