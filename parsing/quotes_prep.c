/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_prep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:39:07 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/09 19:58:15 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prep_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			g_base.quote.nextquote = str[i];
			i++;
			while (str[i])
			{
				if (str[i] == g_base.quote.nextquote)
					break ;
				if (str[i] == ' ')
					str[i] = '\n';
				i++;
			}
		}
		i++;
	}
	return (str);
}

char	*revert_nl_to_sp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = ' ';
		i++;
	}
	return (str);
}

char	**revert_quotes(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i][0] == '\"' || arr[i][0] == '\'')
			arr[i] = revert_nl_to_sp(arr[i]);
		i++;
	}
	return (arr);
}


char	*rm_quote(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (str[0] != 34 && str[0] != 39)
		return (str);
	g_base.quote.nextquote = str[0];
	new_str = malloc(sizeof(char) * ft_strlen(str) - 1);
	while (str[i])
	{
		if (str[i] != g_base.quote.nextquote)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}
