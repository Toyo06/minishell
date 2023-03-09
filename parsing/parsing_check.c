/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:57:35 by mayyildi          #+#    #+#             */
/*   Updated: 2023/02/10 19:00:44 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	op_count(char *str)
{
	int	count;

	count = 0;
	count += op_check(str);
	count += op_check_bis(str);
	count += pipe_check(str);
	return (count);
}

int	op_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (i > 0 && str[i - 1] != ' ')
			{
				error_msg(1);
				return (1);
			}
			if (str[i + 1] == '<')
				i++;
			if (str[i + 1] == '\0')
				return (0);
			if (str[i + 1] != ' ')
			{
				error_msg(1);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	op_check_bis(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			if (i > 0 && str[i - 1] != ' ')
			{
				error_msg(1);
				return (1);
			}
			if (str[i + 1] == '>')
				i++;
			if (str[i + 1] == '\0')
				return (0);
			if (str[i + 1] != ' ')
			{
				error_msg(1);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	pipe_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (i > 0 && (str[i - 1] != ' '))
			{
				error_msg(1);
				return (1);
			}
			if (str[i + 1] == '\0')
				return (0);
			if (str[i + 1] != ' ')
			{
				error_msg(1);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
