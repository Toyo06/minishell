/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:16:57 by mayyildi          #+#    #+#             */
/*   Updated: 2023/02/16 22:38:35 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	check_prompt(char *str, t_list **lst, t_env **env)
{
	int		i;

	i = 0;
	if (!(check_forbidden_char(str)) || !(check_quotes(str)))
		return (0);
	else
	{
		prep_quotes(str);
		g_base.parsing.tab = ft_split(str, ' ');
		g_base.parsing.tab = revert_quotes(g_base.parsing.tab);
		while (g_base.parsing.tab[i])
		{
			g_base.parsing.tab[i] = rm_quote(g_base.parsing.tab[i]);
			i++;
		}
		g_base.quote.returnvalue = list_prep(lst, g_base.parsing.tab, env);
		free(g_base.parsing.tab);
		if (err_management(lst) == 0)
			return (0);
	}
	return (1);
}
