/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:33:00 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/09 22:35:16 by sroggens         ###   ########.fr       */
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
