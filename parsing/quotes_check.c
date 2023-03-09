/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:33:00 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/09 19:58:11 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	g_base.quote.doublequote = 0;
	g_base.quote.simplequote = 0;
	while (str[i])
	{
		if (str[i] == '\"'
			&& g_base.quote.simplequote / 2 * 2 == g_base.quote.simplequote)
			g_base.quote.doublequote++;
		if (str[i] == '\''
			&& g_base.quote.doublequote / 2 * 2 == g_base.quote.doublequote)
			g_base.quote.simplequote++;
		i++;
	}
	i = check_quote_state();
	return (i);
}

int	check_quote_state(void)
{
	if (g_base.quote.doublequote != (g_base.quote.doublequote / 2 * 2))
	{
		printf("Quote not closed.\n");
		return (0);
	}
	if (g_base.quote.simplequote != (g_base.quote.simplequote / 2 * 2))
	{
		printf("Simple quote not closed.\n");
		return (0);
	}
	return (1);
}

