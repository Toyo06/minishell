/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:53:52 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/13 16:50:18 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_arg(char *equal)
{
	char	*arg;
	char	*trimmed_arg;

	arg = ft_strdup(equal + 1);
	trimmed_arg = ft_trim(arg);
	free(arg);
	return (trimmed_arg);
}

char	*ft_trim(char *str)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	j = 0;
	trimmed = malloc(sizeof(char) * ft_strlen(str) - count_quotes(str) + 1);
	while (str[i])
	{
		while (str[i] == 34 || str[i] == 39)
			i++;
		if (str[i] == '\n')
			str[i] = ' ';
		trimmed[j] = str[i];
		i++;
		j++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

int	count_quotes(char *str)
{
	int	i;
	int	count_quotes;

	i = 0;
	count_quotes = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			count_quotes++;
		i++;
	}
	return (count_quotes);
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
